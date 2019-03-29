// Game parameters
const WIDTH = 11;
const HEIGHT = 7;

// Tile Types
const TAB = "#";
const EMPTY = ".";
const ICC = "I";
const BBC = "B";
const DW = "D";
const WIN = "W";
const SC = "S";
const CUT= "C";

// Item Types
const NIL = "NONE";
const DI = "DISH";
const BB = "BLUEBERRIES";
const IC = "ICE_CREAM";
const STWB = "STRAWBERRIES"
const CSTW = "CHOPPED_STRAWBERRIES"

// SPECIAL CHAR

const CL = "XXX";


class Entity{
    constructor(x, y, type){
        this.x = x;
        this.y = y;
        this.type = type;
    }
}

class Item extends Entity{
    constructor(x, y, type){
        super(x, y, type);
    }
}

class Chef extends Entity{

    constructor(x, y, type){
        super(x, y, type);
        this.needs_items = [];
    }

    getPathsToSatisfy(customers, grid){
        var needs_items = [];
        var paths = [];
        for(let i=0; i < customers.length; ++i) {
            let needs_item_for_customer = GAME.customers[i].compareItem(this.type);
            if(!needs_item_for_customer) {
                paths[i] = false;
                continue;
            } else if(needs_item_for_customer.length == 0){
                paths[i] = grid.getCellFromType(WIN).pathToTile(grid, grid.getCell(this.x, this.y), []);
            } else {
                this.stepsToCompleteRecipe(grid, needs_item_for_customer, grid.getCell(this.x, this.y))

            }
            needs_items.push(...new Set(needs_item_for_customer));
        }
        this.needs_items = [...new Set(needs_items)];
    }

    stepsToCompleteRecipe(grid){
        var items = Array(this.needs_items.length);
        for(let i =0; i<items.length;++i){
            //copy the current item state
            let simulate_item = this.type.slice();
            let simulate_location = grid.getCell(this.x, this.y);

            let next_cell = grid.getCellsFromType(needs_items[i]);

            let steps = next_cell.pathToTile(grid,simulate_location, []);
            simulate_item.push(needs_items[i])



            //check if that makes a complete set.
            //if so return steps--else compareItems(new set of items);


            //item state gets reset in loop
        }
    }

    findAllPaths(recipe, cell){
        for(key in recipe){


        }

        //FOR EACH ITEM IN RECIPE GET PATH AND DISTANCE.
            //EXECUTE FIND ALL PATHS ON LAST SQUARE OF JOURNEY
                //SUM AND RETURN THE RESULTS
    }

    findBestPath(recipe, cell){
        //Iterate all Paths and find the shortest.

    }

    findBestPathNice(recipe, cell, chef){


    }
}

class Cell {
    constructor(type, index) {
        this.type = type;
        this.index = index;
        this.x = this.index % WIDTH;
        this.y = Math.floor(this.index / WIDTH);
    }

    canWalkOnIt() {
        return this.type === EMPTY;
    }

    canUseIt(cell){
        let diff_x = Math.abs(cell.x - this.x);
        let diff_y = Math.abs(cell.y - this.y);
        if(diff_x < 2 && diff_y <2){
            return true;
        }
        return false;
    }

    pathToTile(grid, cell, seen_tiles){
        var up, down, left, right;
        seen_tiles.push(cell.index);

        //CAN YOU USE IT FROM HERE?
        if(this.canUseIt(cell)){
            return seen_tiles;
        }

        //WHAT IF YOU MOVE;
        up = grid.getCell(cell.x, cell.y-1);
        down = grid.getCell(cell.x, cell.y+1);
        left = grid.getCell(cell.x-1, cell.y);
        right= grid.getCell(cell.x+1, cell.y);

        var path, best_path;
        if(up!==false && seen_tiles.indexOf(up.index) === -1 && up.canWalkOnIt()){
            path = this.walkDistanceToTile(grid, up, seen_tiles);
            if(path!== undefined && (best_path === undefined || best_path.length>path.length)) best_path = path;
        }
        if(down!==false && seen_tiles.indexOf(down.index) === -1 && down.canWalkOnIt()){
            path = this.walkDistanceToTile(grid, down, seen_tiles);
            if(path!== undefined && (best_path === undefined || best_path.length>path.length)) best_path = path;
        }

        if(left!==false && seen_tiles.indexOf(left.index) === -1 && left.canWalkOnIt()){
            path = this.walkDistanceToTile(grid, left, seen_tiles);
            if(path!== undefined && (best_path === undefined || best_path.length>path.length)) best_path = path;
        }

        if(right!==false && seen_tiles.indexOf(right.index) === -1 && right.canWalkOnIt()){
            path = this.walkDistanceToTile(grid, right, seen_tiles);
            if(path!== undefined && (best_path === undefined || best_path.length>path.length)) best_path = path;
        }
        return best_path;
    }

    useIt(){
        console.log("USE "+this.x +" "+ this.y);
    }

    moveToIt(){
        console.log("MOVE "+this.x +" "+ this.y)
    }


    getPos() {
        return {
            x: this.x,
            y: this.y
        };
    }
}

class Grid{
    constructor(){
        this.cells = [];
        this.items = [];
    }

    addRow(line) {
        for (let i = 0; i < line.length; i++) {
            this.cells.push(new Cell(line[i], this.cells.length));
        }
    }

    getCell(x, y) {
        if(x+WIDTH*y >= 0 && x+WIDTH*y < this.cells.length){
            return this.cells[x + WIDTH * y];
        }
        return false;
    }

    getCellsFromType(type){
        cells = [];
        for(let i=0;i<this.items.length;++i){
            if(this.items[i].type === type){
                cells.push(this.getCell(items[i].x, items[i].y))

            }

        }


        return this.cells.filter(cell => {
            return cell.type === type;
    })[0];
    }


    debug(){
        this.cells.forEach(cell => {
            let pos = cell.getPos();
        console.error(`Cell X: ${pos.x} // Cell Y: ${pos.y}`);
        console.error(`Cell Type: ${cell.type}`);
        console.error(`-------------------------`);
    });
    }
}

class Customer{
    constructor(item, award){
        this.items = item.split('-');
        this.award = award;
    }

    compareItem(item){
        var steps = [];
        //if any part of the item is not part of the recipe dish must be cleared
        steps = JSON.parse(JSON.stringify(this.items));
        for(let i=0;i<item.length;++i){
            if(this.items.indexOf(item[i]) === -1){
                return false;
            }
        }

        steps=steps.filter(function(s){
            return item.indexOf(s) === -1;
        });

        return steps;
    }

    benefitOfStep(steps){
        return this.award / (steps.length+1);
    }
}

class Game{
    constructor(){
        this.grid = new Grid();
        this.chefs = [new Chef(), new Chef()];
        this.customers = [];
    }

    buildItem(playerItem){
        let item = [];

        if(playerItem === NIL){
            return item;
        }
        if(playerItem.indexOf(DI) !== -1){
            item.push(DI);
        }
        if(playerItem.indexOf(BB) !== -1){
            item.push(BB);
        }
        if(playerItem.indexOf(IC) !== -1){
            item.push(IC);
        }
        console.error(item);
        return item;
    }
}

class Agent{
    constructor(Game){
        this.game = Game;
    }


    print(){
        this.bestAction.print()
    }



}


let GAME = new Game();
/**
 * READ GAME SETUP
 */
// ALL CUSTOMERS INPUT: to ignore until Bronze
const numAllCustomers = parseInt(readline());
for (let i = 0; i < numAllCustomers; i++) {
    let inputs = readline().split(' ');
    const customerItem = inputs[0]; // the food the customer is waiting for
    const customerAward = parseInt(inputs[1]); // the number of points awarded for delivering the food
}

// KITCHEN INPUT
for (let i = 0; i < HEIGHT; i++) {
    const kitchenLine = readline();
    GAME.grid.addRow(kitchenLine);
}

var blueberry = GAME.grid.getCellFromType(BBC);
var dishwasher = GAME.grid.getCellFromType(DW);
var icecream = GAME.grid.getCellFromType(ICC);
var customer = GAME.grid.getCellFromType(WIN);
var cutting = GAME.grid.getCellFromType(CUT);
var strawberry = GAME.grid.getCellFromType(STW);

// game loop
while (true) {
    /**
     * READ INPUTS FOR TURN
     */

    // Reset Items
    GAME.grid.items = [];
    // Reset customers
    GAME.customers = [];
    // Reset chefs
    GAME.chefs = [];

    const turnsRemaining = parseInt(readline());

    // PLAYERS INPUT
    let inputsPlayer = readline().split(' ');
    const playerX = parseInt(inputsPlayer[0]);
    const playerY = parseInt(inputsPlayer[1]);
    const playerItem = GAME.buildItem(inputsPlayer[2]);
    GAME.chefs[0] = new Chef(playerX, playerY, playerItem);

    let inputsPartner = readline().split(' ');
    const partnerX = parseInt(inputsPartner[0]);
    const partnerY = parseInt(inputsPartner[1]);
    const partnerItem = GAME.buildItem(inputsPartner[2]);
    GAME.chefs[1] = new Chef(partnerX, partnerY, partnerItem);

    const numTablesWithItems = parseInt(readline()); // the number of tables in the kitchen that currently hold an item
    for (let i = 0; i < numTablesWithItems; i++) {
        let inputs = readline().split(' ');
        const tableX = parseInt(inputs[0]);
        const tableY = parseInt(inputs[1]);
        const item = inputs[2];
        GAME.grid.items.push(new Item(tableX, tableY, item));
    }

    let inputs = readline().split(' ');
    const ovenContents = inputs[0]; // ignore until bronze league
    const ovenTimer = parseInt(inputs[1]);
    const numCustomers = parseInt(readline()); // the number of customers currently waiting for food

    // CURRENT CUSTOMERS INPUT
    for (let i = 0; i < numCustomers; i++) {
        let inputs = readline().split(' ');
        const customerItem = inputs[0];
        const customerAward = parseInt(inputs[1]);
        GAME.customers.push(new Customer(customerItem, customerAward));
    }

    for(let i = 0; i<GAME.chefs.length;++i){
        GAME.chefs[i].compareItems(GAME.customers);
    }

    /**
     * CALCULATE BEST MOVE SEQUENCE
     *
     */

    //FIGURE OUT WHAT ARE VIABLE MOVES TO INCREASE SCORE;

    for (let i = 0; i < GAME.chefs.length; ++i){
        Game.chefs[i].compareItem(GAME.customers)
    }


    let paths = [];






    //CAN THE CHEF PICK SOMETHING UP?
    benefits = Array(4).fill(0);

    console.error(distance)
    for (let i = 0; i < required_steps.length; ++i) {
        console.error("AWARD", GAME.customers[i].award)
        console.error(required_steps[i].indexOf(BB), required_steps[i].indexOf(IC), required_steps[i].indexOf(DI))
        if (required_steps[i].length === 0) {
            benefits[3] = Math.max(benefits[3], GAME.customers[i].award)
        }
        if (required_steps[i].indexOf(CL) !== -1) {
            continue;
        } else {
            if (required_steps[i].indexOf(BB) != -1) {
                benefits[0] = Math.max(benefits[0], GAME.customers[i].award / (distance[0] + 1));
            }
            if (required_steps[i].indexOf(DI) != -1) {
                benefits[1] = Math.max(benefits[1], GAME.customers[i].award / (distance[1] + 1));
            }
            if (required_steps[i].indexOf(IC) != -1) {
                benefits[2] = Math.max(benefits[2], GAME.customers[i].award / (distance[2] + 1));
            }
            if (required_steps[i].indexOf(CSTW) != -1) {
                benefits[2] = Math.max(benefits[2], GAME.customers[i].award / (distance[2] + 1));
            }

        }
    }
    console.error(benefits)
    let has_a_bowl = (GAME.chefs[0].type.indexOf(DI)!== -1);
    let has_nothing = (GAME.chefs[0].type.length === 0);

    if (benefits[3] !== 0) {
        console.error("DISH READY GOING TO CUSTOMER", customer)
        customer.useIt();
    } else if(!has_a_bowl && !has_nothing){
        console.error("NEED A DISH BEFORE CAN GET ANYTHING", dishwasher)
        dishwasher.useIt();
    }else if(Math.max(...benefits)===0){
        console.error("NO GOOD OPTION CLEANING PLATE", dishwasher)
        dishwasher.useIt();
    } else if(benefits[0] >= Math.max(benefits[1], benefits[2])){
        console.error("USING THE BLUEBERRY", blueberry)
        blueberry.useIt();
    } else if (benefits[1] >= benefits[2]){
        console.error("DISHWASHER IS CLOSER", dishwasher)
        dishwasher.useIt();
    }else{
        console.error("GOING FOR SOME ICECREAM", icecream)
        icecream.useIt();
    }
}