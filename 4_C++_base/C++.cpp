/*
def initialize_beliefs(grid):
    height = len(grid)
    width = len(grid[0])
    area = height * width
    belief_per_cell = 1.0 / area
    beliefs = []
    for i in range(height):
        row = []
        for j in range(width):
            row.append(belief_per_cell)
        beliefs.append(row)
    return beliefs
    */

vector<vector<float>> initiallize_beliefs(vector< vector<float> > grid)
{
    int height = grid.size();
    int width = grid[0].size();
    int area = height * width;
    float belief_per_cell = 1.0 / area;
    vector<float> row(width, belief_per_cell);
    vector<vector<float>> beliefs(height, row);
    return beliefs;
}

/*
def sense(color, grid, beliefs, p_hit, p_miss):
    new_beliefs = []
    new_row = []
    for i in range(len(grid)):
        for j in range(len(grid[0])):
            hit = (grid[i][j] == color)
            new_row.append(hit*beliefs[i][j] * p_hit + (1 - hit)*beliefs[i][j] * p_miss)
        new_beliefs.append(new_row)
        new_row = []
    return normalize(new_beliefs)
    */

vector<vector<float>> sense(char color, vector<vector<char>> grid, vector<vector<float>> beliefs, float p_hit, float p_miss)
{
    vector<vector<float>> new_beliefs;
    vector<float> new_row;
    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[0].size(); j++)
        {
            int hit = (grid[i][j] == color);
            new_row.push_back(hit*beliefs[i][j]*p_hit + (1-hit)*beliefs[i][j]*p_miss);
        }
        new_beliefs.push_back(new_row);
        new_row.clear();
    }
return normalize(new_beliefs);
}

/*
def move(dy, dx, beliefs, blurring):
    height = len(beliefs)
    width = len(beliefs[0])
    new_G = [[0.0 for i in range(width)] for j in range(height)]
    for i, row in enumerate(beliefs):
        for j, cell in enumerate(row):
            new_i = (i + dy) % height
            new_j = (j + dx) % width
            # pdb.set_trace()
            new_G[int(new_i)][int(new_j)] = cell
    return blur(new_G, blurring)
*/

vector<vector<float>> move(int dy, int dx, vector<vector<float>> beliefs, float blurring)
{
    int height = beliefs.size();
    int width = beliefs[0].size();
    vector<vector<float>> new_G(height, vector<float>(width, 0.0));
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int new_i = (i + dy + height) % height;
            int new_j = (j + dx + width) % width;
            new_G[new_i][new_j] = beliefs[i][j];
        }
    }
    return blur(new_G, blurring);
}

/*
def normalize(grid):
    """
    Given a grid of unnormalized probabilities, computes the
    correspond normalized version of that grid.
    """
    total = 0.0
    for row in grid:
        for cell in row:
            total += cell
    for i,row in enumerate(grid):
        for j,cell in enumerate(row):
            grid[i][j] = float(cell) / total
    return grid
*/

vector<vector<float>> normalize(vector<vector<float>> grid)
{
    float total = 0.0;
    for (vector<float> row : grid)
    {
        for (float cell : row)
        {
            total += cell;
        }
    }
    int height = grid.size();
    int width = grid[0].size();
    for (int i = 0; i < height; i++) 
    {
        for (int j = 0; j < width; j++)
        {
            grid[i][j] = grid[i][j] / total;
        }
    }
    return grid;
}

/*
def blur(grid, blurring):
    """
    Spreads probability out on a grid using a 3x3 blurring window.
    The blurring parameter controls how much of a belief spills out
    into adjacent cells. If blurring is 0 this function will have
    no effect.
    """
    height = len(grid)
    width  = len(grid[0])

    center_prob = 1.0-blurring
    corner_prob = blurring / 12.0
    adjacent_prob = blurring / 6.0

    window = [
            [corner_prob,  adjacent_prob,  corner_prob],
            [adjacent_prob, center_prob,  adjacent_prob],
            [corner_prob,  adjacent_prob,  corner_prob]
        ]
    new = [[0.0 for i in range(width)] for j in range(height)]
    for i in range(height):
        for j in range(width):
            grid_val = grid[i][j]
            for dx in range(-1,2):
                for dy in range(-1,2):
                    mult = window[dx+1][dy+1]
                    new_i = (i + dy) % height
                    new_j = (j + dx) % width
                    new[new_i][new_j] += mult * grid_val
    return normalize(new)
*/

vector<vector<float>> blur(vector<vector<float>> grid, float blurring)
{
    int height = grid.size();
    int width = grid[0].size();
    float center_prob = 1.0 - blurring;
    float corner_prob = blurring / 12.0;
    float adjacent_prob = blurring / 6.0;
    vector<float> row1 = { corner_prob, adjacent_prob, corner_prob };
    vector<float> row2 = { adjacent_prob, center_prob, corner_prob };
    vector<float> row3 = { corner_prob, adjacent_prob, corner_prob };
    vector<vector<float>> window;
    window.push_back(row1);
    window.push_back(row2);
    window.push_back(row3);
    // new可能是保留字，这里不能使用，所以通过new_grid代替
    vector<vector<float>> new_grid(height, vector<float>(width, 0.0));
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float grid_val = grid[i][j];
            for (int dx = -1; dx < 2; dx++)
            {
                for (int dy = -1; dy < 2; dy++)
                {
                    float mult = window[dx + 1][dy + 1];
                    float new_i = (i + dy + height) % height;
                    float new_j = (j + dx + width) % width;
                    new_grid[new_i][new_j] += mult * grid_val;

                }
            }
        }
    }
    return normalize(new_grid);
}