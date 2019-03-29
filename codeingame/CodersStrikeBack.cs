using System;
using System.Linq;
using System.IO;
using System.Text;
using System.Collections;
using System.Collections.Generic;
using System.Diagnostics;

class Physic{
    public static double distance2(Point p1, Point p2){
        return (p1.X()-p2.X())*(p1.X()-p2.X()) + (p1.Y()-p2.Y())*(p1.Y()-p2.Y());
    }

    public static double distance(Point p1, Point p2){
        return Math.Sqrt(distance2(p1, p2));
    }

    public static Point midPoint(Point p1, Point p2){
      double x = (double)Math.Round(p1.X() + p2.X())/2;
      double y = (double)Math.Round(p1.Y() + p2.Y())/2;
      return new Point(x,y);
    }

    public  static double triArea(Point p1, Point p2, Point p3){
        return Math.Abs((p1.X() * (p2.Y()-p3.Y())+ p2.X() * (p3.Y()-p1.Y())+p3.X() * (p1.Y()-p2.Y()))/2);
    }

}

class Map{
 public const int MAX_X = 9;
 public Checkpoint start;
}

class Point{
    public double x;
    public double y;

    public Point(double x_pos, double y_pos){
      x = x_pos;
      y = y_pos;
    }

    public double X(){
        return x;
    }

    public double Y(){
        return y;
    }

    public void setX(double x_pos){
        x=x_pos;
    }

    public void setY(double y_pos){
        y = y_pos;
    }


}

class Unit:Point{
  int id;
  double RAD;
  public double vx;
  public double vy;
  public double speed;

  public Unit(double radius, double x_pos, double y_pos) : base(x_pos, y_pos){
     RAD = radius;
     vx=0;
     vy=0;
     speed = 0;
  }

   public void update(double pos_x, double pos_y){
        vx = (pos_x - x) * 0.85;
        vy = (pos_y - y) * 0.85;
        this.setX(pos_x);
        this.setY(pos_y);
        speed = (double)Math.Sqrt(vx*vx+vy*vy);
    }
}

class Checkpoint:Unit{
    Checkpoint next;
    Checkpoint prev;
    public Checkpoint(Checkpoint prevCP, double x_pos, double y_pos):base((double)600, x_pos, y_pos){
        prev = prevCP;
    }

    public void setPrev(Checkpoint cp){
        prev = cp;
    }
    public void setNext(Checkpoint cp){
        next = cp;
    }
    public Checkpoint getNext(){
        return next;
    }

     public Checkpoint getPrev(){
        return prev;
    }
}

class Pod:Unit{
    public bool canBoosted;
    public double angle;
    int nextCheckPointId;
    int timeout;
    bool shield;

    public Pod(double X, double Y):base((double)400, X, Y){
      angle = 0;
      shield = false;
    }

    public Pod Clone(){
        Pod clone = new Pod(X(), Y());
        clone.setAngle(angle);
        clone.vx = vx;
        clone.vy = vy;
        return clone;

    }

    public void setAngle(double a){
        angle = a;
    }

    public string getOutput(Move move){
       return Conversion.getOutput(move, this);
    }

    public string debug(){
        string output =  "X: " + X() + " Y: " + Y() + "  vX:" + vx + " vY:" + vy + " angle:"+angle;
        return output;
    }
    /*
    public double getAngle(Point p) {
        double d = Physic.distance(this, p);
        double dx = (p.x - this.X()) / d;
        double dy = (p.y - this.Y()) / d;

        // Simple trigonometry. We multiply by 180.0 / PI to convert radiants to degrees.
        double a = Math.Acos(dx) * 180.0 / Math.PI;

        // If the point I want is below me, I have to shift the angle for it to be correct
        if (dy < 0) {
            a = 360.0 - a;
        }

        return a;
    }

    public double diffAngle(Point p) {
        double a = this.getAngle(p);

        // To know whether we should turn clockwise or not we look at the two ways and keep the smallest
        // The ternary operators replace the use of a modulo operator which would be slower
        double right = this.angle <= a ? a - this.angle : 360.0 - this.angle + a;
        double left = this.angle >= a ? this.angle - a : this.angle + 360.0 - a;

        if (right < left) {
            return right;
        } else {
            // We return a negative angle if we must rotate to left
            return -left;
        }
    }
    */

    public void rotate(double a) {

        // Can't turn by more than 18° in one turn
        if (a > 18.0) {
            a = 18.0;
        } else if (a < -18.0) {
            a = -18.0;
        }

        this.angle += a;

        // The % operator is slow. If we can avoid it, it's better.
        if (this.angle >= 360.0) {
            this.angle = this.angle - 360.0;
        } else if (this.angle < 0.0) {
            this.angle += 360.0;
        }
    }

    public void boost(double thrust) {
      // Don't forget that a pod which has activated its shield cannot accelerate for 3 turns
        if (this.shield) {
            return;
        }

        // Conversion of the angle to radiants
        double ra = this.angle * Math.PI / 180.0;

        // Trigonometry
        this.vx += Math.Cos(ra) * thrust;
        this.vy += Math.Sin(ra) * thrust;
    }

    public double move(double t, Checkpoint target) {
        double time = 0;
        double go_next = 0;

        while(time < t){
            x += vx * 0.1;
            y += vy * 0.1;

            if(go_next == 0){
                if(Physic.distance2(this, target) < 250000){
                    go_next = time + 0.1;
                }

            }
            time += 0.1;
        }
        return go_next;
    }

    public void end() {
        this.x = (double)Math.Round(this.x);
        this.y = (double)Math.Round(this.y);
        this.vx = this.vx * 0.85;
        this.vy = this.vy * 0.85;

        // Don't forget that the timeout goes down by 1 each turn. It is reset to 100 when you pass a checkpoint
        this.timeout -= 1;
    }
    public double simulate(Move move, Checkpoint target) {
        double go_next;
        this.rotate(move.dAngle);
        this.boost(move.thrust);
        go_next = this.move(1.0, target);
        this.end();
        return go_next;
    }

     public double simulate(Gene gene, Checkpoint target, Checkpoint next_target) {
        int x = 0;
        bool gone_next = false;
        double go_next=0;
        while (x<3){
            if(gone_next == false){
                go_next = this.simulate(gene.moves[x], target);
                if(go_next != 0){
                    go_next += x;
                    gone_next = true;
                }
            } else {
                this.simulate(gene.moves[x], next_target);
            }

            x+=1;
        }
        return go_next;
     }
}


class Gene{
    public List<Move> moves;
    public double score;

    public Gene(){
     moves = new List<Move>();
     moves.Add(new Move());
     moves.Add(new Move());
     moves.Add(new Move());
    }

    public Gene(Random rnd){
        moves = new List<Move>();
        moves.Add(new Move(rnd));
        moves.Add(new Move(rnd));
        moves.Add(new Move(rnd));
    }

    public Gene(Move m1, Move m2, Move m3){
      moves = new List<Move>();
      moves.Add(m1);
      moves.Add(m2);
      moves.Add(m3);
    }

    public Gene Breed (Gene partner, Random rnd){
        Gene child = new Gene();
        child.moves.Add(moves[0].Breed(partner.moves[0], rnd));
        child.moves.Add(moves[1].Breed(partner.moves[1], rnd));
        child.moves.Add(moves[2].Breed(partner.moves[2], rnd));
        return child;
    }

    public void Optimize (Pod p, Checkpoint target, Checkpoint next_target){
        int x = 0;
        double diff_score = 1;
        double time_to_next = 0;
        double scoreTurnUp, scoreTurnDown, scoreSpeedUp, scoreSpeedDown;
        double old_score = -1000;

        Pod clone;

        // Find direction of maximal improvement ..
        while(old_score<score){
            old_score = score;
            while(x<3){
                scoreTurnUp = -1000;
                scoreTurnDown = -1000;
                scoreSpeedDown = -1000;
                scoreSpeedUp = -1000;

                if(moves[x].dAngle < 18){
                    clone = p.Clone();
                    moves[x].dAngle += 0.5;
                    time_to_next = clone.simulate(this, target, next_target);
                    scoreTurnUp = this.Evaluate(clone, target, next_target, time_to_next);
                    if(scoreTurnUp > score){
                        score = scoreTurnUp;
                    } else {
                      moves[x].dAngle -= 0.5;
                      if(moves[x].dAngle > -18){
                          clone = p.Clone();
                          moves[x].dAngle -= 0.5;
                          time_to_next = clone.simulate(this, target, next_target);
                          scoreTurnDown = this.Evaluate(clone, target, next_target, time_to_next);
                          if(scoreTurnDown > score){
                            score = scoreTurnDown;
                          } else {
                            moves[x].dAngle += 0.5;
                          }

                      }
                    }
                }

                if(moves[x].thrust < 100){
                   clone = p.Clone();
                   moves[x].thrust += 1;
                   time_to_next = clone.simulate(this, target, next_target);
                   scoreSpeedUp = this.Evaluate(clone, target, next_target, time_to_next);
                   if(scoreSpeedUp>score){
                    score=scoreSpeedUp;
                   } else{
                        moves[x].thrust -= 1;
                        if(moves[x].thrust > 0){
                              clone = p.Clone();
                              moves[x].thrust -= 1;
                              time_to_next = clone.simulate(this, target, next_target);
                              scoreSpeedDown = this.Evaluate(clone, target, next_target, time_to_next);

                              if(scoreSpeedDown> score ){
                                score = scoreSpeedDown;
                              } else {
                                moves[x].thrust += 1;
                              }
                        }
                   }
                }
                x+=1;
            }
        }

    }

    public static int CompareGenesByScore(Gene a, Gene b){
        if (a.score > b.score){
            return -1;

        } else if (a.score == b.score){
            return 0;
        }else {
            return 1;
        }
    }


    public double Evaluate(Pod pod, Checkpoint t, Checkpoint t2, double time_to_target){
        double new_score = 0;
        Checkpoint target;
        if(time_to_target == 0){
            target = t;

        } else {
            target = t2;
            score += 500;
        }
        double distance_target = Math.Max(Physic.distance2(pod, target)-50000, 0) * 0.0000001;

        //double triangle_area = Physic.triArea(future_pod, pod, target)*0.0001;
        //double dDistance =  (distance_1_turn - distance_target) * -0.1;


        //while(angle_to_target > 180){angle_to_target = Math.Abs(angle_to_target - 360);}
        new_score -= distance_target - 10* time_to_target;
        Console.Error.WriteLine("SCORE: " + score + "Distance" +distance_target );
        return new_score;
    }
}

class Move{
  public double dAngle;
  public double thrust;

  public Move(){
    dAngle = 0;
    thrust = 100;
  }

  public Move(Random rnd){
    dAngle = Math.Min(18, Math.Max(-18, rnd.Next(-36,36)));
    thrust = Math.Min(100, rnd.Next(0, 200));
  }

  public Move(double diff_Angle, double f){
    dAngle = diff_Angle;
    thrust = f;
  }

  public Move Breed(Move mv, Random rnd){
    int select = rnd.Next(0,3);
    double ang;
    double f;
    if(select == 0){
     ang = dAngle;
    } else if (select == 1){
     ang = mv.dAngle;
    } else {
     ang = (mv.dAngle + dAngle)/2;
    }

    select = rnd.Next(0,3);
    if(select == 0){
     f = thrust;
    } else if (select == 1){
     f = mv.thrust;
    } else {
     f = (mv.thrust + thrust)/2;
    }
    f =Math.Min(100, Math.Max(0, f+rnd.Next(-5,5)));
    ang =Math.Min(18, Math.Max(-18, ang+rnd.Next(-3,3)));

    return new Move(ang, f);
  }
}

class Conversion{
   public static double twoPointsAngle(Point p1, Point p2){
       double dy = p2.Y() - p1.Y();
       double dx = p2.X() - p1.X();
       return Math.Atan2(dy, dx) * 57.296;
   }

   public static string getOutput(Move move, Pod pod){
        double a = pod.angle + move.dAngle;

        a = a * Math.PI / 180.0;
        double px = pod.X() + Math.Cos(a) * 10000.0;
        double py = pod.Y() + Math.Sin(a) * 10000.0;

        string output = (int)px + " " + (int)py + " " + move.thrust;
        return output;
    }
   // Take Thrust and Rotation Command  ==> return targetX,targetY, Thrust

}

class Game
{
    static void Main(string[] args)
    {
        string[] inputs;
        bool has_boosted = false;
        Point prevPoint = new Point(0, 0);
        Checkpoint start = null;
        Checkpoint target = null;
        Checkpoint next_target = null;
        Pod myPod =null;
        Pod simPod = null;
        double target_angle =0;
        Random rnd = new Random();
        Gene genome = null;
        Gene bestMove = new Gene();

        // game loop
        while (true)
        {
            //Simulation will hold all of the possible sequences of moves
            List<Gene> simulation = new List<Gene>();


            inputs = Console.ReadLine().Split(' ');
            double pod_x = double.Parse(inputs[0]);
            double pod_y = double.Parse(inputs[1]);
            double nextCheckpointX = double.Parse(inputs[2]); // x position of the next check point
            double nextCheckpointY = double.Parse(inputs[3]); // y position of the next check point
            double nextCheckpointDist = double.Parse(inputs[4]); // distance to the next checkpoint
            double nextCheckpointAngle = double.Parse(inputs[5]); // angle between your pod orientation and the direction of the next checkpoint
            inputs = Console.ReadLine().Split(' ');
            //Point opponent = new Point(double.Parse(inputs[0]), double.Parse(inputs[1]));

            /*
            *RECORD GAME STATE.
            */


            if(start == null){
             start = new Checkpoint (null, nextCheckpointX, nextCheckpointY);
             target = start;

            } else if (start.getPrev() != null){
                if(target.X() != nextCheckpointX && target.Y() != nextCheckpointY){
                 target = target.getNext();
                }

            } else {
               if (target.X() != nextCheckpointX && target.Y() != nextCheckpointY){
                    //new target;
                   if(start.X() == nextCheckpointX && start.Y() == nextCheckpointY){
                       //close the loop;
                       target.setNext(start);
                       start.setPrev(target);
                       target = start;
                   } else {
                     Checkpoint tmp = new Checkpoint(target, nextCheckpointX, nextCheckpointY);
                     tmp.setPrev(target);
                     target.setNext(tmp);
                     target = tmp;
                   }
                }
            }

            if(target.getNext() == null){
                next_target = new Checkpoint (null, 8000, 4500);
            } else {
                next_target = target.getNext();
            }


            if(myPod == null){
              myPod = new Pod (pod_x, pod_y);
              target_angle = Conversion.twoPointsAngle(myPod, start);
              myPod.setAngle(target_angle - nextCheckpointAngle);

            } else {
                myPod.update(pod_x, pod_y);
                target_angle = Conversion.twoPointsAngle(myPod, target);
                myPod.setAngle(target_angle -nextCheckpointAngle);
            }
            int x = 0;
            double thrust = 100;

            simPod = myPod.Clone();
            double time_to_target = 0;
            bool target_hit = false;
            double go_next=0;
            Checkpoint tmp_target;


            x=0;
            while (x < 25){
                simPod = myPod.Clone();
                go_next = 0;

                Gene random_sequence = new Gene(rnd);
                go_next = simPod.simulate(random_sequence, target, next_target);
                random_sequence.score = random_sequence.Evaluate(simPod, target, next_target, go_next);
                simulation.Add(random_sequence);
                x += 1;
            }


           int z = 0;
           int y = 0;
           int q = 0;


            simulation.Sort(Gene.CompareGenesByScore);
            simulation = simulation.GetRange(0, 2);
            while(z < 2){
                simPod = myPod.Clone();
                simulation[z].Optimize(simPod, target, next_target);
                z+=1;
            }


            simulation.Sort(Gene.CompareGenesByScore);
            bestMove = simulation[0];

            Console.Error.WriteLine("GENETIC BEST MOVE VALUE: " + bestMove.score + " dAngle: "+ bestMove.moves[0].dAngle +"thrust:"  + bestMove.moves[0].thrust );


            string Output =  Conversion.getOutput(bestMove.moves[0], myPod);
            Console.WriteLine(Output);
        }
    }
}














