#include<bits/stdc++.h>
using namespace std;

char my_color, oponent_color;
ofstream log_file;

int minVal(char grid[8][8], int n, int depth, int alpha, int beta);
int maxVal(char grid[8][8], int n, int depth, int alpha, int beta);

void getBoard(char grid[8][8], int n)
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            cin>>grid[i][j];
        }
    }
}

int getNoOfColor(char grid[8][8], int n, int x, int y, int i, int j)
{
    int no_of_color = 0;
    while(x>=0 && x<n && y>=0 && y<n)
    {
        if(grid[x][y]!='e') no_of_color++;
        x = x + i;
        y = y + j;
    }

    return no_of_color;
}

bool isValidMove(char grid[8][8], int n, int x, int y, int i, int j, int dist, char color)
{
    if(x+(i*dist)<0 || x+(i*dist)>=n || y+(j*dist)<0 || y+(j*dist)>=n)
        return false;

    int p=x+(i*dist), q=y+(j*dist);
    while(x!=p || y!=q)
    {
        if(grid[x][y]!='e' && grid[x][y]!=color)
            return false;
        x = x + i;
        y = y + j;
    }

    if(grid[x][y] == color)
        return false;

    return true;
}

void printBoard(char grid[8][8], int n)
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            log_file<<grid[i][j]<<" ";
        }
        log_file<<endl;
    }
}

bool hasWon(char grid[8][8], int n, char color)
{
    int visited[8][8] = {0}, x=-1, y=-1;

    queue<pair<int, int>> que;
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(grid[i][j] == color)
            {
                x=i;
                y=j;
            }
        }
    }

    que.push(make_pair(x, y));
    visited[x][y] = 1;
    while(!que.empty())
    {
        pair<int, int> point = que.front();
        que.pop();
        if((point.first+1)<n && grid[point.first+1][point.second]==color && visited[point.first+1][point.second]==0)
        {
            que.push(make_pair(point.first+1, point.second));
            visited[point.first+1][point.second] = 1;
        }
        if((point.first-1)>=0 && grid[point.first-1][point.second]==color && visited[point.first-1][point.second]==0)
        {
            que.push(make_pair(point.first-1, point.second));
            visited[point.first-1][point.second] = 1;
        }
        if((point.second+1)<n && grid[point.first][point.second+1]==color && visited[point.first][point.second+1]==0)
        {
            que.push(make_pair(point.first, point.second+1));
            visited[point.first][point.second+1] = 1;
        }
        if((point.second-1)>=0 && grid[point.first][point.second-1]==color && visited[point.first][point.second-1]==0)
        {
            que.push(make_pair(point.first, point.second-1));
            visited[point.first][point.second-1] = 1;
        }
        if((point.first+1)<n && (point.second+1)<n && grid[point.first+1][point.second+1]==color && visited[point.first+1][point.second+1]==0)
        {
            que.push(make_pair(point.first+1, point.second+1));
            visited[point.first+1][point.second+1] = 1;
        }
        if((point.first+1)<n && (point.second-1)>=0 && grid[point.first+1][point.second-1]==color && visited[point.first+1][point.second-1]==0)
        {
            que.push(make_pair(point.first+1, point.second-1));
            visited[point.first+1][point.second-1] = 1;
        }
        if((point.first-1)>=0 && (point.second+1)<n && grid[point.first-1][point.second+1]==color && visited[point.first-1][point.second+1]==0)
        {
            que.push(make_pair(point.first-1, point.second+1));
            visited[point.first-1][point.second+1] = 1;
        }
        if((point.first-1)>=0 && (point.second-1)>=0 && grid[point.first-1][point.second-1]==color && visited[point.first-1][point.second-1]==0)
        {
            que.push(make_pair(point.first-1, point.second-1));
            visited[point.first-1][point.second-1] = 1;
        }
    }

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(grid[i][j] == color && visited[i][j]==0)
            {
                return false;
            }
        }
    }
    return true;
}

int findCluster(char grid[8][8], int n, int cluster[8][8], int colors_in_cluster[], char color)
{
    int cluster_size = 0;

    for(int i=0; i<n; i++)
    {
        colors_in_cluster[2*i] = 0;
        colors_in_cluster[2*i+1] = 0;
        for(int j=0; j<n; j++)
        {
            cluster[i][j] = -1;
        }
    }

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(grid[i][j] == color && cluster[i][j]==-1)
            {
                queue<pair<int, int>> que;
                que.push(make_pair(i, j));
                cluster[i][j] = cluster_size;
                while(!que.empty())
                {
                    pair<int, int> point = que.front();
                    colors_in_cluster[cluster_size]++;
                    que.pop();
                    if((point.first+1)<n && grid[point.first+1][point.second]==color && cluster[point.first+1][point.second]==-1)
                    {
                        que.push(make_pair(point.first+1, point.second));
                        cluster[point.first+1][point.second] = cluster_size;
                    }
                    if((point.first-1)>=0 && grid[point.first-1][point.second]==color && cluster[point.first-1][point.second]==-1)
                    {
                        que.push(make_pair(point.first-1, point.second));
                        cluster[point.first-1][point.second] = cluster_size;
                    }
                    if((point.second+1)<n && grid[point.first][point.second+1]==color && cluster[point.first][point.second+1]==-1)
                    {
                        que.push(make_pair(point.first, point.second+1));
                        cluster[point.first][point.second+1] = cluster_size;
                    }
                    if((point.second-1)>=0 && grid[point.first][point.second-1]==color && cluster[point.first][point.second-1]==-1)
                    {
                        que.push(make_pair(point.first, point.second-1));
                        cluster[point.first][point.second-1] = cluster_size;
                    }
                    if((point.first+1)<n && (point.second+1)<n && grid[point.first+1][point.second+1]==color && cluster[point.first+1][point.second+1]==-1)
                    {
                        que.push(make_pair(point.first+1, point.second+1));
                        cluster[point.first+1][point.second+1] = cluster_size;
                    }
                    if((point.first+1)<n && (point.second-1)>=0 && grid[point.first+1][point.second-1]==color && cluster[point.first+1][point.second-1]==-1)
                    {
                        que.push(make_pair(point.first+1, point.second-1));
                        cluster[point.first+1][point.second-1] = cluster_size;
                    }
                    if((point.first-1)>=0 && (point.second+1)<n && grid[point.first-1][point.second+1]==color && cluster[point.first-1][point.second+1]==-1)
                    {
                        que.push(make_pair(point.first-1, point.second+1));
                        cluster[point.first-1][point.second+1] = cluster_size;
                    }
                    if((point.first-1)>=0 && (point.second-1)>=0 && grid[point.first-1][point.second-1]==color && cluster[point.first-1][point.second-1]==-1)
                    {
                        que.push(make_pair(point.first-1, point.second-1));
                        cluster[point.first-1][point.second-1] = cluster_size;
                    }
                }
                cluster_size++;
            }
        }
    }

    return cluster_size;
}

int heuristicFunc(char grid[8][8], int n)
{
    int value, my_dist=0, oponent_dist=0, my_cluster[8][8], oponent_cluster[8][8], my_cluster_size=0, oponent_cluster_size=0, my_colors_in_cluster[2*n], oponent_colors_in_cluster[2*n];
    int nMove1=0, nMove2=0, nColor1=0, nColor2=0, max_cluster1=-1, max_cluster2=-1, mx=-1, n_me=0, n_oponent=0, my_x=0, my_y=0, oponent_x=0, oponent_y=0;
    int x_mx_cluster1=0, y_mx_cluster1=0, x_mx_cluster2=0, y_mx_cluster2=0;

    my_cluster_size = findCluster(grid, n, my_cluster, my_colors_in_cluster, my_color);
    oponent_cluster_size = findCluster(grid, n, oponent_cluster, oponent_colors_in_cluster, oponent_color);

    if(my_cluster_size == 1) return 10000;
    if(oponent_cluster_size == 1) return -10000;

    for(int i=0; i<my_cluster_size; i++)
    {
        if(my_colors_in_cluster[i]>mx)
        {
            mx = my_colors_in_cluster[i];
            max_cluster1 = i;
        }
    }
    mx = -1;
    for(int i=0; i<oponent_cluster_size; i++)
    {
        if(oponent_colors_in_cluster[i]>mx)
        {
            mx = oponent_colors_in_cluster[i];
            max_cluster2 = i;
        }
    }

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(grid[i][j] == my_color)
            {
                if(max_cluster1==my_cluster[i][j])
                {
                    x_mx_cluster1 += i;
                    y_mx_cluster1 += j;
                }
                n_me++;
                my_x += i;
                my_y += j;
            }
            else if(grid[i][j] == oponent_color)
            {
                if(max_cluster2==oponent_cluster[i][j])
                {
                    x_mx_cluster2 += i;
                    y_mx_cluster2 += j;
                }
                n_oponent++;
                oponent_x += i;
                oponent_y += j;
            }
        }
    }

    double my_avg_x = 1.00*my_x/n_me;
    double my_avg_y = 1.00*my_y/n_me;
    double oponent_avg_x = 1.00*oponent_x/n_oponent;
    double oponent_avg_y = 1.00*oponent_y/n_oponent;

    //cout<<my_avg_x<<" "<<my_avg_y<<" "<<oponent_avg_x<<" "<<oponent_avg_y<<endl;

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(grid[i][j] == my_color)
            {
                if(max_cluster1!=my_cluster[i][j])
                    my_dist += (int)(pow(1.00*x_mx_cluster1/my_colors_in_cluster[max_cluster1]-i,2)+pow(1.00*y_mx_cluster1/my_colors_in_cluster[max_cluster1]-j,2));
                //cout<<"my "<<i<<" "<<j<<endl;
                //cout<<my_dist<<endl;
                /*if(my_color == 'b')
                {
                    my_dist += (int)abs(oponent_avg_y-j);
                    my_dist += (int)abs(my_avg_x-i);
                }
                else
                {
                    my_dist += (int)abs(oponent_avg_x-i);
                    my_dist += (int)abs(my_avg_y-j);
                }*/
                //cout<<my_dist<<endl;
            }
            else if(grid[i][j] == oponent_color)
            {
                if(max_cluster2!=oponent_cluster[i][j])
                    oponent_dist += (int)(pow(1.00*x_mx_cluster2/oponent_colors_in_cluster[max_cluster2]-i,2)+pow(1.00*y_mx_cluster2/oponent_colors_in_cluster[max_cluster2]-j,2));
                //cout<<"opo "<<i<<" "<<j<<endl;
                //cout<<oponent_dist<<endl;
                /*if(my_color == 'b')
                {
                    oponent_dist += (int)abs(my_avg_y-j);
                    oponent_dist += (int)abs(oponent_avg_x-i);
                }
                else
                {
                    oponent_dist += (int)abs(oponent_avg_x-i);
                    oponent_dist += (int)abs(my_avg_y-j);
                }*/
                //cout<<oponent_dist<<endl;
            }
        }
    }

    //cout<<my_dist<<" "<<oponent_dist<<endl;

    my_dist += 50*my_colors_in_cluster[max_cluster1];
    oponent_dist += 50*oponent_colors_in_cluster[max_cluster2];

    my_dist += 10*(int)(pow(1.00*(n-1)/2-1.00*x_mx_cluster1/my_colors_in_cluster[max_cluster1],2)+pow(1.00*(n-1)/2-1.00*y_mx_cluster1/my_colors_in_cluster[max_cluster1],2));
    oponent_dist += 10*(int)(pow(1.00*(n-1)/2-1.00*x_mx_cluster2/oponent_colors_in_cluster[max_cluster2],2)+pow(1.00*(n-1)/2-1.00*y_mx_cluster2/oponent_colors_in_cluster[max_cluster2],2));

    //cout<<my_dist<<" "<<oponent_dist<<endl;

    value = oponent_dist - my_dist;

    return value;
}

int maxVal(char grid[8][8], int n, int depth, int alpha, int beta)
{
    if(depth == 0 || hasWon(grid, n, oponent_color))
        return heuristicFunc(grid, n);

    vector<pair<pair<int, int>, pair<int, int>>> moves;
    int up_down_color, right_left_color, diagonal1_color, diagonal2_color, n_oponent=0;

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(grid[i][j] == my_color)
            {
                up_down_color = getNoOfColor(grid, n, 0, j, 1, 0);
                right_left_color = getNoOfColor(grid, n, i, 0, 0, 1);
                diagonal1_color = getNoOfColor(grid, n, i-min(i,j), j-min(i,j), 1, 1);
                diagonal2_color = getNoOfColor(grid, n, (i+j>=(n-1))? (n-1):(i+j), (i+j>=(n-1))?(i+j-(n-1)):0, -1, 1);

                //move up
                if(isValidMove(grid, n, i, j, -1, 0, up_down_color, my_color))
                {
                    moves.push_back(make_pair(make_pair(i, j), make_pair(i-up_down_color, j)));
                }
                //move down
                if(isValidMove(grid, n, i, j, 1, 0, up_down_color, my_color))
                {
                    moves.push_back(make_pair(make_pair(i, j), make_pair(i+up_down_color, j)));
                }
                //move right
                if(isValidMove(grid, n, i, j, 0, 1, right_left_color, my_color))
                {
                    moves.push_back(make_pair(make_pair(i, j), make_pair(i, j+right_left_color)));
                }
                //move left
                if(isValidMove(grid, n, i, j, 0, -1, right_left_color, my_color))
                {
                    moves.push_back(make_pair(make_pair(i, j), make_pair(i, j-right_left_color)));
                }
                //move up right
                if(isValidMove(grid, n, i, j, -1, 1, diagonal2_color, my_color))
                {
                    moves.push_back(make_pair(make_pair(i, j), make_pair(i-diagonal2_color, j+diagonal2_color)));
                }
                //move up left
                if(isValidMove(grid, n, i, j, -1, -1, diagonal1_color, my_color))
                {
                    moves.push_back(make_pair(make_pair(i, j), make_pair(i-diagonal1_color, j-diagonal1_color)));
                }
                //move down right
                if(isValidMove(grid, n, i, j, 1, 1, diagonal1_color, my_color))
                {
                    moves.push_back(make_pair(make_pair(i, j), make_pair(i+diagonal1_color, j+diagonal1_color)));
                }
                //move down left
                if(isValidMove(grid, n, i, j, 1, -1, diagonal2_color, my_color))
                {
                    moves.push_back(make_pair(make_pair(i, j), make_pair(i+diagonal2_color, j-diagonal2_color)));
                }
            }
            else if(grid[i][j]==oponent_color)
                n_oponent++;
        }
    }

    pair<pair<int, int>, pair<int, int>> branch;
    int temp;

    for(int i=0; i<moves.size(); i++)
    {
        branch = moves[i];
        if(grid[branch.second.first][branch.second.second]==my_color && n_oponent<=n/2)
            continue;
        if(grid[branch.second.first][branch.second.second]==oponent_color)
        {
            if((branch.second.first<n/4 && branch.second.second<n/4) || (branch.second.first>=n-n/4 && branch.second.second>=n-n/4) || (branch.second.first<n/4 && branch.second.second>=n-n/4) || (branch.second.first>=n-n/4 && branch.second.second<n/4))
                continue;
        }
        char changed_grid[8][8];
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                changed_grid[i][j] = grid[i][j];
            }
        }
        changed_grid[branch.first.first][branch.first.second] = 'e';
        changed_grid[branch.second.first][branch.second.second] = my_color;

        temp = minVal(changed_grid, n, depth-1, alpha, beta);
        /*if(my_color=='b' && grid[branch.second.first][branch.second.second]=='r' && branch.second.second>=2 && branch.second.second<=(n-2))
            temp += 10*n_oponent-20*abs(n/2 - branch.second.second);
        else if(my_color=='r' && grid[branch.second.first][branch.second.second]=='b' && branch.second.first>=2 && branch.second.first<=(n-2))
            temp += 10*n_oponent-20*abs(n/2 - branch.second.first);*/

        if(temp>alpha)
        {
            alpha = temp;
            if(alpha >= beta) break;
        }
    }

    return alpha;
}

int minVal(char grid[8][8], int n, int depth, int alpha, int beta)
{
    if(depth == 0 || hasWon(grid, n, my_color))
        return heuristicFunc(grid, n);

    vector<pair<pair<int, int>, pair<int, int>>> moves;
    int up_down_color, right_left_color, diagonal1_color, diagonal2_color, n_me=0;

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(grid[i][j] == oponent_color)
            {
                up_down_color = getNoOfColor(grid, n, 0, j, 1, 0);
                right_left_color = getNoOfColor(grid, n, i, 0, 0, 1);
                diagonal1_color = getNoOfColor(grid, n, i-min(i,j), j-min(i,j), 1, 1);
                diagonal2_color = getNoOfColor(grid, n, (i+j>=(n-1))? (n-1):(i+j), (i+j>=(n-1))?(i+j-(n-1)):0, -1, 1);

                //move up
                if(isValidMove(grid, n, i, j, -1, 0, up_down_color, oponent_color))
                {
                    moves.push_back(make_pair(make_pair(i, j), make_pair(i-up_down_color, j)));
                }
                //move down
                if(isValidMove(grid, n, i, j, 1, 0, up_down_color, oponent_color))
                {
                    moves.push_back(make_pair(make_pair(i, j), make_pair(i+up_down_color, j)));
                }
                //move right
                if(isValidMove(grid, n, i, j, 0, 1, right_left_color, oponent_color))
                {
                    moves.push_back(make_pair(make_pair(i, j), make_pair(i, j+right_left_color)));
                }
                //move left
                if(isValidMove(grid, n, i, j, 0, -1, right_left_color, oponent_color))
                {
                    moves.push_back(make_pair(make_pair(i, j), make_pair(i, j-right_left_color)));
                }
                //move up right
                if(isValidMove(grid, n, i, j, -1, 1, diagonal2_color, oponent_color))
                {
                    moves.push_back(make_pair(make_pair(i, j), make_pair(i-diagonal2_color, j+diagonal2_color)));
                }
                //move up left
                if(isValidMove(grid, n, i, j, -1, -1, diagonal1_color, oponent_color))
                {
                    moves.push_back(make_pair(make_pair(i, j), make_pair(i-diagonal1_color, j-diagonal1_color)));
                }
                //move down right
                if(isValidMove(grid, n, i, j, 1, 1, diagonal1_color, oponent_color))
                {
                    moves.push_back(make_pair(make_pair(i, j), make_pair(i+diagonal1_color, j+diagonal1_color)));
                }
                //move down left
                if(isValidMove(grid, n, i, j, 1, -1, diagonal2_color, oponent_color))
                {
                    moves.push_back(make_pair(make_pair(i, j), make_pair(i+diagonal2_color, j-diagonal2_color)));
                }
            }
            else if(grid[i][j] == my_color)
                n_me++;
        }
    }

    pair<pair<int, int>, pair<int, int>> branch;
    int temp;

    for(int i=0; i<moves.size(); i++)
    {
        branch = moves[i];
        if(grid[branch.second.first][branch.second.second]==my_color && n_me<=n/2)
            continue;
        if(grid[branch.second.first][branch.second.second]==my_color)
        {
            if((branch.second.first<n/4 && branch.second.second<n/4) || (branch.second.first>=n-n/4 && branch.second.second>=n-n/4) || (branch.second.first<n/4 && branch.second.second>=n-n/4) || (branch.second.first>=n-n/4 && branch.second.second<n/4))
                continue;
        }
        char changed_grid[8][8];
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                changed_grid[i][j] = grid[i][j];
            }
        }
        changed_grid[branch.first.first][branch.first.second] = 'e';
        changed_grid[branch.second.first][branch.second.second] = oponent_color;

        temp = maxVal(changed_grid, n, depth-1, alpha, beta);
        /*if(oponent_color=='b' && grid[branch.second.first][branch.second.second]=='r' && branch.second.second>=2 && branch.second.second<=(n-2))
            temp -= 10*n_me-20*abs(n/2 - branch.second.second);
        else if(oponent_color=='r' && grid[branch.second.first][branch.second.second]=='b' && branch.second.first>=2 && branch.second.first<=(n-2))
            temp -= 10*n_me-20*abs(n/2 - branch.second.first);*/

        if(temp<beta)
        {
            beta = temp;
            if(alpha >= beta) break;
        }
    }
    return beta;
}

void alphaBeta(char grid[8][8], int n, int depth)
{
    int alpha = INT_MIN;
    int beta = INT_MAX;
    vector<pair<pair<int, int>, pair<int, int>>> moves;
    int up_down_color, right_left_color, diagonal1_color, diagonal2_color, n_oponent=0;

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(grid[i][j] == my_color)
            {
                up_down_color = getNoOfColor(grid, n, 0, j, 1, 0);
                right_left_color = getNoOfColor(grid, n, i, 0, 0, 1);
                diagonal1_color = getNoOfColor(grid, n, i-min(i,j), j-min(i,j), 1, 1);
                diagonal2_color = getNoOfColor(grid, n, (i+j>=(n-1))? (n-1):(i+j), (i+j>=(n-1))?(i+j-(n-1)):0, -1, 1);

                //move up
                if(isValidMove(grid, n, i, j, -1, 0, up_down_color, my_color))
                {
                    moves.push_back(make_pair(make_pair(i, j), make_pair(i-up_down_color, j)));
                }
                //move down
                if(isValidMove(grid, n, i, j, 1, 0, up_down_color, my_color))
                {
                    moves.push_back(make_pair(make_pair(i, j), make_pair(i+up_down_color, j)));
                }
                //move right
                if(isValidMove(grid, n, i, j, 0, 1, right_left_color, my_color))
                {
                    moves.push_back(make_pair(make_pair(i, j), make_pair(i, j+right_left_color)));
                }
                //move left
                if(isValidMove(grid, n, i, j, 0, -1, right_left_color, my_color))
                {
                    moves.push_back(make_pair(make_pair(i, j), make_pair(i, j-right_left_color)));
                }
                //move up right
                if(isValidMove(grid, n, i, j, -1, 1, diagonal2_color, my_color))
                {
                    moves.push_back(make_pair(make_pair(i, j), make_pair(i-diagonal2_color, j+diagonal2_color)));
                }
                //move up left
                if(isValidMove(grid, n, i, j, -1, -1, diagonal1_color, my_color))
                {
                    moves.push_back(make_pair(make_pair(i, j), make_pair(i-diagonal1_color, j-diagonal1_color)));
                }
                //move down right
                if(isValidMove(grid, n, i, j, 1, 1, diagonal1_color, my_color))
                {
                    moves.push_back(make_pair(make_pair(i, j), make_pair(i+diagonal1_color, j+diagonal1_color)));
                }
                //move down left
                if(isValidMove(grid, n, i, j, 1, -1, diagonal2_color, my_color))
                {
                    moves.push_back(make_pair(make_pair(i, j), make_pair(i+diagonal2_color, j-diagonal2_color)));
                }
            }
            else if(grid[i][j]==oponent_color)
                n_oponent++;
        }
    }

    printBoard(grid, n);

    pair<pair<int, int>, pair<int, int>> branch;
    int x1=-1, y1=-1, x2=-1, y2=-1, temp;

    for(int i=0; i<moves.size(); i++)
    {
        branch = moves[i];
        if(grid[branch.second.first][branch.second.second]==my_color && n_oponent<=n/2)
            continue;
        if(grid[branch.second.first][branch.second.second]==oponent_color)
        {
            if((branch.second.first<n/4 && branch.second.second<n/4) || (branch.second.first>=n-n/4 && branch.second.second>=n-n/4) || (branch.second.first<n/4 && branch.second.second>=n-n/4) || (branch.second.first>=n-n/4 && branch.second.second<n/4))
                continue;
        }
        char changed_grid[8][8];
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                changed_grid[i][j] = grid[i][j];
            }
        }
        changed_grid[branch.first.first][branch.first.second] = 'e';
        changed_grid[branch.second.first][branch.second.second] = my_color;

        temp = minVal(changed_grid, n, depth-1, alpha, beta);
        /*if(my_color=='b' && grid[branch.second.first][branch.second.second]=='r' && branch.second.second>=2 && branch.second.second<=(n-2))
            temp += 10*n_oponent-20*abs(n/2 - branch.second.second);
        else if(my_color=='r' && grid[branch.second.first][branch.second.second]=='b' && branch.second.first>=2 && branch.second.first<=(n-2))
            temp += 10*n_oponent-20*abs(n/2 - branch.second.first);*/
        //cout<<branch.first.first<<" "<<branch.first.second<<" "<<branch.second.first<<" "<<branch.second.second<<" "<<temp<<endl;

        if(temp>alpha)
        {
            alpha = temp;
            x1 = branch.first.first;
            y1 = branch.first.second;
            x2 = branch.second.first;
            y2 = branch.second.second;
        }
    }

    log_file<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<endl<<endl;
    cout<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<endl;
}


int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);
    //freopen("input.txt","r", stdin);
    char grid[8][8];
    log_file.open("log2.txt");

    /*int board_size = 8;
    my_color = 'b';
    oponent_color = 'r';
    int depth = 5;*/

    int board_size = stoi(argv[2]);
    int depth;
    if(board_size == 6) depth = 5;
    else depth = 4;
    my_color = argv[1][0];
    if(my_color == 'r') oponent_color = 'b';
    else oponent_color = 'r';

    log_file << "my type: " << my_color << endl;
    log_file << "board size: " << board_size << endl;
    while(true)
    {
        getBoard(grid, board_size);
        alphaBeta(grid, board_size, depth);
    }

    log_file.close();
    return 0;
}

