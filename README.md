# How To Run The Project:

 Create a `.rlg327` folder in your home directory:
```bash
mkdir ~/.rlg327
```

Build the project:
```bash
make
```

## Running configurations
Run the project with flags (or no flags):
```bash
./dungeon
```

### Load a dungeon
```bash
./dungeon --load
```

### Generate and Save a Dungeon
```bash
./dungeon --save
```

### Load and Save a Dungeon
```bash
./dungeon --load --save
```

> # Dungeon File
> Whenever a save or load occurs, it uses the file called `dungeon`. This doesn't have any extension and cannot have one for loading to work.

# Main Files:
```Plain
/
├── include/
│   ├── dijkstra.h
│   └── priority_queue.h
└── src/
    ├── core/
    │   └── priority_queue.c
    ├── pathfinding/
    │   └── dijkstra.c
    └── main.c
```
# About the Project:

## Constraints:
- All files and inputs are assumed to be valid

## How the Project Runs:
After loading or generating a new dungeon, the program runs Dijkstra's algorithm twice. Once for non-tunneling distance maps, and once for tunneling distance maps. This implementation of the algorithm is located in `dijkstra.c`, and uses a generic, indexed priority queue (min-heap) located in `priority_queue.c` to run the algorithm. The `main.c` file runs the program.

# Example Output:
```plain
----------------------------------------------------------------------------------
|                                                                                |
|          ....  ....                                                            |
|          ....  ....                                                            |
|          ....  ....                             ......          ....    ....   |
|          ....###################################......          ....    ....   |
|          ....##  #                   ###########....<.##########....    ....   |
|          ....#   #                   #  ....@                   ....    ....   |
|     #####....###########################.....                   ....    ....   |
|     #    ....##>#..........#############.....################           ....   |
|     #    ....    ..........          #    #                 #           ....   |
|  ...... #....    ..........#>###########################################....   |
|  ......##....    ...>......          #    #                 #           ....   |
|  ......# ....    #      ##    ........................................  ....   |
|      ##  ....    #       ##   ........................................##....   |
| .......  ....    #        ##  ........................................  ....   |
| .......####################################                 #           ....   |
| .......          #          ##......<.......         ..............     ....   |
|                  #############..............#########..............            |
|                               ..............         ..............            |
|                                                                                |
|                                                                                |
----------------------------------------------------------------------------------
----------------------------------------------------------------------------------
|                                                                                |
|          5444  9888                                                            |
|          5433  9877                                                            |
|          5432  9876                             456789          1123    5555   |
|          543210987654321098765432109876543222223456789          0123    4444   |
|          543210  7                   7654321112345678901234567890123    3333   |
|          54321   7                   7  4321@                   0123    2222   |
|     09876543210987654321098765432109876543211                   1123    1112   |
|     0    5432109876543210987654321098765432222345678901234567           0012   |
|     0    5432    7654321098          7    3                 7           9012   |
|  321098 65433    76543210987654321098876544456789012345678988890123456789012   |
|  321098765444    7654321098          8    5                 9           9012   |
|  3210987 5555    7      09    5432109998766678901234567890100012345678  0012   |
|      98  6544    8       09   5432100098777778901234567890111112345678901112   |
| 4321099  6543    8        98  5432111098888888901234567890122222345678  1222   |
| 4321009876543210987654321098765432221099999                 3           2233   |
| 4321109          8          7654333210000000         01234544456789     3334   |
|                  87654321098765444321111111112345678901234555556789            |
|                               55543222222222         01234566666789            |
|                                                                                |
|                                                                                |
----------------------------------------------------------------------------------
----------------------------------------------------------------------------------
|                                                                                |
| 644321876543210988765332198887532119998866555565556799012346800023346790134445 |
| 543109876543210987755321198777532109876555544444456789012346899022234780112235 |
| 543109886543210987654321098765432109876543333333456789012345689011234780011223 |
| 532109986543210987654321098765432109876543222223456789012345678901234789001123 |
| 532100886543210987654321098765432109876543211123456789012345678901234578900123 |
| 53210987654321098765432109876543210987654321@123456789012345678901234567990123 |
| 542109876543210987654321098765432109876543211123456789012345679901234567890124 |
| 542109876543210987654321098765432109876543222223456789012345678001234667890124 |
| 432109876543210987654321098765432109876543333333456789012345678901234567890125 |
| 432109876543321087654321098765432109876544444445556789012345678901234567890123 |
| 432109876543322087654321098765432109876555555555666789012345678901234567890123 |
| 432109876543221187654321098865432109887776666666777789012345678901234567890123 |
| 432109886543210988754321098875432109988877777777788889012345678901234567890123 |
| 432109876543210987654321098765432100999888888888889999012345678901234567890123 |
| 432109876543210987654321098765432110009999999999999000012345678901234568990123 |
| 432109876543210987654321098765432211100000001000001111233445678901234668900123 |
| 432109987755331987654321098765433222111111111221111222234455678901234668901123 |
| 432211988766531987654321098765443332222222222222222233334556678901234568002334 |
| 433332199776631987776321099975544433333333333333344444444566778901234568022344 |
|                                                                                |
----------------------------------------------------------------------------------
```