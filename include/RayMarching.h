#pragma once
#include<vector>
//i dont know why i created this class

class marchrays{
  public:

virtual void show_map() =0;
virtual void update() =0;

virtual void DrawMap(std::vector<std::vector<int>>& map){
    int map_width=map[0].size();
    int map_height=map.size();


}

};
