#include "Player.hh"


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME DJCUBITOv11


struct PLAYER_NAME : public Player {

  /**
   * Factory: returns a new instance of this class.
   * Do not modify this function.
   */
  static Player* factory () {
    return new PLAYER_NAME;
  }

  /**
   * Types and attributes for your player can be defined here.
   */
  
  typedef vector< vector<bool> > Mvis;
  typedef vector< vector<int> > Mtrop;
  
  bool posicio_valida_w(int i, int j) {
    if(cell(i,j).type == Wall) 
      return false;
    return true;
  }
  
  int envoltat(int i, int j) {
   int count = 1; 
   vector<int> is = {1,2,1,1,0,0,0,0,-1,-1,-1,-2};
   vector<int> js = {0,0,1,-1,1,2,-1,-2,1,-1,0,0};
   for(int k = 0; k < 12; k++) {
     if(i+is[k] >= 0 && i+is[k] < 37 && j+js[k] >= 0 && j+js[k] < 37 && cell(i+is[k],j+js[k]).id != -1 && unit(cell(i+is[k],j+js[k]).id).player != 0 && unit(cell(i+is[k],j+js[k]).id).type != Witch)
       count++;
   }
   return count;
  }
  
  bool no_mata_unitat(int i, int j, Mvis m) {
    bool aliat = false;
    vector<int> is = {1,2,1,1,0,0,0,0,-1,-1,-1,-2};
    vector<int> js = {0,0,1,-1,1,2,-1,-2,1,-1,0,0};
    for(int k = 0; k < 12 and not aliat; k++) {
      if(i+is[k] >= 0 && i+is[k] < 37 && j+js[k] >= 0 && j+js[k] < 37 && cell(i+is[k],j+js[k]).id != -1 && m[i+is[k]][j+js[k]]) aliat = true;
    }
    if(aliat) return false;
    else return true;
  }
  
  Pos moviment_w(int x, int y, Mvis m, Mtrop& cab) {
   queue<Pos> p;
   bool trobat = false;
   Mvis m2(37,vector<bool>(37,false));
   vector<int> is = {1,-1,0,0};
   vector<int> js = {0,0,1,-1};
   p.push({x,y});
   m[x][y] = true;
   Pos pos;
   while(not p.empty() && not trobat) {
     pos = p.front();
     p.pop();
     int i = pos.i;
     int j = pos.j;
     if(cell(i,j).id != -1 && unit(cell(i,j).id).player != 0 && unit(cell(i,j).id).type != Witch && no_mata_unitat(i,j,m) && cab[i][j] == 0 && envoltat(i,j) >= 3) {
      trobat = true; 
      cab[i][j]++;
     }
     for(int k = 0; k < 4; k++) {
	if(posicio_valida_w(i+is[k],j+js[k]) && not m2[i+is[k]][j+js[k]]) {
	  p.push({i+is[k],j+js[k]});
	  m2[i+is[k]][j+js[k]] = true;
	}
      }
   }
   if(trobat) 
     return pos;
   else 
     return {-1,-1};
  }
  
  int distancia_w(int xo, int yo, int xn, int yn) {
    queue<Pos> p;
    queue<int> d;
    bool trobat = false;
    Mvis m(37,vector<bool>(37,false));
    vector<int> is = {1,-1,0,0};
    vector<int> js = {0,0,1,-1};
    p.push({xo,yo});
    m[xo][yo] = true;
    d.push(0);
    Pos pos;
    int dist;
    while(not p.empty() && not trobat) {
      pos = p.front();
      dist = d.front();
      p.pop();
      d.pop();
      int i = pos.i;
      int j = pos.j;
      if(i == xn && j == yn) 
	trobat = true;
      for(int k = 0; k < 4; k++) {
	if(posicio_valida_w(i+is[k],j+js[k]) && not m[i+is[k]][j+js[k]]) {
	  p.push({i+is[k],j+js[k]});
	  d.push(dist+1);
	  m[i+is[k]][j+js[k]] = true;
	}
      }
    }
    if(trobat) return dist;
    return -1;
  }
  
  int min_dist_w(vector<int> v) {
    int min = v[0];
    for(unsigned int i = 1; i < v.size(); i++) {
      if(v[i] < min) min = v[i];
    }
    return min;
  }
  
  Dir direccio_w(Pos old_pos, Pos new_pos, Mvis& m) {
    int dist = distancia_w(old_pos.i,old_pos.j,new_pos.i,new_pos.j);
    if(dist > 0) {
      vector<int> d(4,-1);
      if(posicio_valida_w(old_pos.i+1,old_pos.j) && not m[old_pos.i+1][old_pos.j] && no_mata_unitat(old_pos.i+1,old_pos.j,m)) {
	d[0] = distancia_w(old_pos.i+1,old_pos.j,new_pos.i,new_pos.j);
      }
      if(posicio_valida_w(old_pos.i-1,old_pos.j) && not m[old_pos.i-1][old_pos.j] && no_mata_unitat(old_pos.i-1,old_pos.j,m)) {
	d[1] = distancia_w(old_pos.i-1,old_pos.j,new_pos.i,new_pos.j);
      }
      if(posicio_valida_w(old_pos.i,old_pos.j+1) && not m[old_pos.i][old_pos.j+1] && no_mata_unitat(old_pos.i,old_pos.j+1,m)) {
	d[2] = distancia_w(old_pos.i,old_pos.j+1,new_pos.i,new_pos.j);
      }
      if(posicio_valida_w(old_pos.i,old_pos.j-1) && not m[old_pos.i][old_pos.j-1] && no_mata_unitat(old_pos.i,old_pos.j-1,m)) {
	d[3] = distancia_w(old_pos.i,old_pos.j-1,new_pos.i,new_pos.j);
      }
      vector<int> v;
      for(int i = 0; i < 4; i++) {
	if(d[i] >= 0) v.push_back(d[i]);
      }
      if(v.size() > 0) {
	int min = min_dist_w(v);
	if(min == d[0]) {
	  m[old_pos.i+1][old_pos.j] = true;
	  return Bottom;
	}
	else if(min == d[1]) {
	  m[old_pos.i-1][old_pos.j] = true;
	  return Top;
	}
	else if(min == d[2]) {
	  m[old_pos.i][old_pos.j+1] = true;
	  return Right;
	}
	else if(min == d[3]) {
	  m[old_pos.i][old_pos.j-1] = true;
	  return Left;
	}
	else {
	  return None;
	}
      }
    }
  return None;
  }
  
   
  bool posicio_valida_f(int i, int j) {
    if(cell(i,j).type == Wall) return false;
    if(cell(i,j).haunted) return false;
    return true;
  }
  
  int distancia_f(int xo, int yo, int xn, int yn) {
    queue<Pos> p;
    queue<int> d;
    bool trobat = false;
    Mvis m(37,vector<bool>(37,false));
    vector<int> is = {1,-1,0,0};
    vector<int> js = {0,0,1,-1};
    p.push({xo,yo});
    m[xo][yo] = true;
    d.push(0);
    Pos pos;
    int dist;
    while(not p.empty() && not trobat) {
      pos = p.front();
      dist = d.front();
      p.pop();
      d.pop();
      int i = pos.i;
      int j = pos.j;
      if(i == xn && j == yn) 
	trobat = true;
      for(int k = 0; k < 4; k++) {
	if(posicio_valida_f(i+is[k],j+js[k]) && not m[i+is[k]][j+js[k]]) {
	  p.push({i+is[k],j+js[k]});
	  d.push(dist+1);
	  m[i+is[k]][j+js[k]] = true;
	}
      }
    }
    if(trobat) return dist;
    return -1;
  }
	 
  Pos moviment_f(int x, int y, Mvis& ocupat) {
    queue<Pos> p;
    bool trobat = false;
    Mvis m(37, vector<bool> (37,false));
    vector<int> is = {1,-1,0,0};
    vector<int> js = {0,0,1,-1};
    p.push({x,y});
    m[x][y] = true;
    Pos pos;
    while(not p.empty() && not trobat) {
      pos = p.front();
      p.pop();
      int i = pos.i;
      int j = pos.j;
      if(cell(i,j).id == -1 && cell(i,j).owner != 0 && not ocupat[i][j]) { 
	ocupat[i][j] = true;
	trobat = true;
      }
      for(int k = 0; k < 4; k++) {
	if(posicio_valida_f(i+is[k],j+js[k]) && not m[i+is[k]][j+js[k]]) {
	  p.push({i+is[k],j+js[k]});
	  m[i+is[k]][j+js[k]] = true;
	}
      }
    }
    if(trobat)
      return pos;
    else 
      return {-1,-1};
  }
  
  int min_dist_f(vector<int> v) {
    int min = v[0];
    for(unsigned int i = 1; i < v.size(); i++) {
      if(v[i] < min) min = v[i];
    }
    return min;
  }
  
  Dir direccio_f(Pos old_pos, Pos new_pos, Mvis& m) {
    int dist = distancia_f(old_pos.i,old_pos.j,new_pos.i,new_pos.j);
    if(dist > 0) {
      vector<int> d(4,-1);
      if(posicio_valida_f(old_pos.i+1,old_pos.j) && not m[old_pos.i+1][old_pos.j]) {
	d[0] = distancia_f(old_pos.i+1,old_pos.j,new_pos.i,new_pos.j);
      }
      if(posicio_valida_f(old_pos.i-1,old_pos.j) && not m[old_pos.i-1][old_pos.j]) {
	d[1] = distancia_f(old_pos.i-1,old_pos.j,new_pos.i,new_pos.j);
      }
      if(posicio_valida_f(old_pos.i,old_pos.j+1) && not m[old_pos.i][old_pos.j+1]) {
	d[2] = distancia_f(old_pos.i,old_pos.j+1,new_pos.i,new_pos.j);
      }
      if(posicio_valida_f(old_pos.i,old_pos.j-1) && not m[old_pos.i][old_pos.j-1]) {
	d[3] = distancia_f(old_pos.i,old_pos.j-1,new_pos.i,new_pos.j);
      } 
      vector<int> v;
      for(int i = 0; i < 4; i++) {
	if(d[i] >= 0) v.push_back(d[i]);
      }
      if(v.size() > 0) {
	int min = min_dist_f(v);
	if(min == d[0]) {
	  m[old_pos.i+1][old_pos.j] = true;
	  return Bottom;
	}
	else if(min == d[1]) {
	  m[old_pos.i-1][old_pos.j] = true;
	  return Top;
	}
	else if(min == d[2]) {
	  m[old_pos.i][old_pos.j+1] = true;
	  return Right;
	}
	else if(min == d[3]) {
	  m[old_pos.i][old_pos.j-1] = true;
	  return Left;
	}
	else 
	  return None;
      }
    }
  return None;
  }
  
  bool posicio_valida_k(int i, int j) {
    if(cell(i,j).type == Wall) return false;
    if(cell(i,j).haunted) return false;
    return true;
  }
  
  int min_dist_k(vector<int> v) {
    int min = v[0];
    for(unsigned int i = 1; i < v.size(); i++) {
      if(v[i] < min) min = v[i];
    }
    return min;
  }
  
  Dir direccio_k(Pos old_pos, Pos new_pos, Mvis& m) {
    int dist = distancia_k(old_pos.i,old_pos.j,new_pos.i,new_pos.j);
    if(dist > 0) {
      vector<int> d(8,-1);
      if(posicio_valida_k(old_pos.i-1,old_pos.j-1) && not m[old_pos.i-1][old_pos.j-1]) {
	d[0] = distancia_k(old_pos.i-1,old_pos.j-1,new_pos.i,new_pos.j);
      }
      if(posicio_valida_k(old_pos.i+1,old_pos.j+1) && not m[old_pos.i+1][old_pos.j+1]) {
	d[1] = distancia_k(old_pos.i+1,old_pos.j+1,new_pos.i,new_pos.j);
      }
      if(posicio_valida_k(old_pos.i-1,old_pos.j+1) && not m[old_pos.i-1][old_pos.j+1]) {
	d[2] = distancia_k(old_pos.i-1,old_pos.j+1,new_pos.i,new_pos.j);
      }
      if(posicio_valida_k(old_pos.i+1,old_pos.j-1) && not m[old_pos.i+1][old_pos.j-1]) {
	d[3] = distancia_k(old_pos.i+1,old_pos.j-1,new_pos.i,new_pos.j);
      } 
      if(posicio_valida_k(old_pos.i+1,old_pos.j) && not m[old_pos.i+1][old_pos.j]) {
	d[4] = distancia_k(old_pos.i+1,old_pos.j,new_pos.i,new_pos.j);
      }
      if(posicio_valida_k(old_pos.i-1,old_pos.j) && not m[old_pos.i-1][old_pos.j]) {
	d[5] = distancia_k(old_pos.i-1,old_pos.j,new_pos.i,new_pos.j);
      }
      if(posicio_valida_k(old_pos.i,old_pos.j+1) && not m[old_pos.i][old_pos.j+1]) {
	d[6] = distancia_k(old_pos.i,old_pos.j+1,new_pos.i,new_pos.j);
      }
      if(posicio_valida_k(old_pos.i,old_pos.j-1) && not m[old_pos.i][old_pos.j-1]) {
	d[7] = distancia_k(old_pos.i,old_pos.j-1,new_pos.i,new_pos.j);
      }
      vector<int> v;
      for(int i = 0; i < 8; i++) {
	if(d[i] >= 0) v.push_back(d[i]);
      }
      if(v.size() > 0) {
	int min = min_dist_k(v);
	if(min == d[0]) {
	  m[old_pos.i-1][old_pos.j-1] = true;
	  return TL;
	}
	else if(min == d[1]) {
	  m[old_pos.i+1][old_pos.j+1] = true;
	  return BR;
	}
	else if(min == d[2]) {
	  m[old_pos.i-1][old_pos.j+1] = true;
	  return RT;
	}
	else if(min == d[3]) {
	  m[old_pos.i+1][old_pos.j-1] = true;
	  return LB;
	}
	else if(min == d[4]) {
	  m[old_pos.i+1][old_pos.j] = true;
	  return Bottom;
	}
	else if(min == d[5]) {
	  m[old_pos.i-1][old_pos.j] = true;
	  return Top;
	}
	else if(min == d[6]) {
	  m[old_pos.i][old_pos.j+1] = true;
	  return Right;
	}
	else if(min == d[7]) {
	  m[old_pos.i][old_pos.j-1] = true;
	  return Left;
	}
	  
	else 
	  return None;
      }
    }
    return None;
      
      
  }
  
  int distancia_k(int xo, int yo, int xn, int yn) {
    queue<Pos> p;
    queue<int> d;
    bool trobat = false;
    Mvis m(37,vector<bool>(37,false));
    vector<int> is = {1,-1,0,0,1,-1,-1,1};
    vector<int> js = {0,0,1,-1,1,-1,1,-1};
    p.push({xo,yo});
    m[xo][yo] = true;
    d.push(0);
    Pos pos;
    int dist;
    while(not p.empty() && not trobat) {
      pos = p.front();
      dist = d.front();
      p.pop();
      d.pop();
      int i = pos.i;
      int j = pos.j;
      if(i == xn && j == yn) 
	trobat = true;
      for(int k = 0; k < 8; k++) {
	if(posicio_valida_f(i+is[k],j+js[k]) && not m[i+is[k]][j+js[k]]) {
	  p.push({i+is[k],j+js[k]});
	  d.push(dist+1);
	  m[i+is[k]][j+js[k]] = true;
	}
      }
    }
    if(trobat) return dist;
    return -1;
  }
  
   Pos moviment_k(int x, int y, Mtrop& cab) {
    queue<Pos> p;
    Mvis m(37, vector<bool> (37,false));
    vector<int> is = {1,-1,0,0,1,-1,-1,1};
    vector<int> js = {0,0,1,-1,1,-1,1,-1};
    bool trobat = false;
    p.push({x,y});
    m[x][y] = true;
    Pos pos;
    while(not p.empty() && not trobat) {
      pos = p.front();
      p.pop();
      int i = pos.i;
      int j = pos.j;
      if(cell(i,j).id != -1 && unit(cell(i,j).id).type != Witch && unit(cell(i,j).id).player != 0 && cab[i][j] <= 4)  {
	trobat = true;
	cab[i][j]++;
      }
      for(int k = 0; k < 8; k++) {
	if(posicio_valida_k(i+is[k],j+js[k]) && not m[i+is[k]][j+js[k]]) {
	  p.push({i+is[k],j+js[k]});
	  m[i+is[k]][j+js[k]] = true;
	}
      }
    }
    if(trobat) return pos;
    else return {-1,-1};
   }

  /**
   * Play method, invoked once per each round.
   */
  virtual void play () {
    Mvis ocupat(37, vector<bool>(37,false));
    Mtrop cab(37, vector<int>(37,0));
    Mvis m(37, vector<bool> (37,false));
    vector<int> vf = farmers(0);
    for(int id : vf) {
      Pos pos = unit(id).pos;
      Pos new_pos = moviment_f(pos.i, pos.j,ocupat); 
      if(new_pos.i == -1 && new_pos.j == -1) command(id,None);
      else {
	Dir dir_nm = direccio_f(pos,new_pos,m);
	command(id,dir_nm);
      }
    }
    vector<int> vk = knights(0);
    for(int id : vk) {
      Pos pos = unit(id).pos;
      Pos new_pos = moviment_k(pos.i, pos.j, cab); 
      if(new_pos.i == -1 && new_pos.j == -1) command(id,None);
      else {
	Dir dir_nm = direccio_k(pos,new_pos,m);
	command(id,dir_nm);
      }
    }
    vector<int> vw = witches(0);
    for(int id : vw) {
      Pos pos = unit(id).pos;
      Pos new_pos = moviment_w(pos.i, pos.j, m,cab);
      if(new_pos.i == -1 && new_pos.j == -1) command(id,None);
      else {
	Dir dir_nm = direccio_w(pos,new_pos,m);
	command(id,dir_nm);
      }
    }
  }

};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
