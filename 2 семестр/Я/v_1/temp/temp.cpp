





using namespace std;

void down(int &n_x, int &n_y, vector<vector<int>> &map, int &x_d, int &y_d, int &falling)
{
   for(int i = n_x; i > 0; i--)
      {
         for(int k = n_y-1; k > -1; k--)
         {
            if(map[i][k+1] == 0)
            {
               if(i == x_d and k == y_d)
               {
                  y_d += 1;
               }
               map[i][k+1] = map[i][k];
               map[i][k] = 0;
            }
            else
            {
               if(i == x_d and k == y_d)
               {
                  falling = 0;
               }
            }
         }
      }
}

void move_line(vector<vector<int>> &map, int &x_d, int y_d, int turn)
{
   if(map[x_d+turn][y_d] == 0 and map[x_d+turn][y_d-1] == 0 and map[x_d+turn][y_d-2] == 0)
   {
      map[x_d+turn][y_d] = map[x_d][y_d];
      map[x_d+turn][y_d-1] = map[x_d][y_d-1];
      map[x_d+turn][y_d-2] = map[x_d][y_d-2];
      map[x_d][y_d] = 0;
      map[x_d][y_d-1] = 0;
      map[x_d][y_d-2] = 0;
      x_d += turn;
   }
}

void checking(vector<vector<int>> &map, int n_x, int n_y, int &kol)
{
   int again = 1;
   while(again == 1)
   {
      again = 0;
      for(int i = 3; i < n_y; i++)
      {
         int n = 0, col = 0;
         for(int k = 1; k < n_x; k++)
         {
            if(col == map[k][i])
            {
               n++;
            }
            else
            {
               if(n > 2 and col != 0)
               {
                  again = 1;
                  kol++;
                  for(int l = 0; l < n; l++)
                  {
                     map[k-l-1][i] = 0;
                  }
               }
               n = 1;
               col = map[k][i];
            }
         }
         if(n > 2 and col != 0)
         {
            again = 1;
            kol++;
            for(int l = 0; l < n; l++)
            {
               map[n_x-1-l][i] = 0;
            }
         }
      }
      
      for(int i = 1; i < n_x; i++)
      {
         int n = 0, col = 0;
         for(int k = 3; k < n_y; k++)
         {
            if(col == map[i][k])
            {
               n++;
            }
            else
            {
               if(n > 2 and col != 0)
               {
                  again = 1;
                  kol++;
                  for(int l = 0; l < n; l++)
                  {
                     map[i][k-l-1] = 0;
                  }
               }
               n = 1;
               col = map[i][k];
            }
         }
         if(n > 2 and col != 0)
         {
            again = 1;
            kol++;
            for(int l = 0; l < n; l++)
            {
               map[i][n_y-1-l] = 0;
            }
         }
      }
   }
}

int main()
{
   vector<vector<int>> map;
   vector<vector<int>> obj;
   
   for(int i = 0; i < 2; i++)
   {
      obj.push_back({});
      for(int k = 0; k < 3; k++)
      {
         _abracadabra_cast(obj[i]);