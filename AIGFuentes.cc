#include "Player.hh"
#include <queue>
#define PLAYER_NAME AIGFuentes


struct PLAYER_NAME : public Player {

  static Player* factory () {return new PLAYER_NAME;}

///////////////////////////////////////////////////////////////////////////////////////////////

typedef vector<bool> VB;
typedef vector<VB> VBB;
typedef vector<int> VI;
typedef vector<VI> VII;


int busca_any_w(VBB tablero, VII distancias, queue<Pos> edges, Pos &pos_desti, VBB &celdas_w){

  
  while(edges.empty() == false){
    Pos pos_act = edges.front();
   if(celdas_w[pos_act.i][pos_act.j] == false and cell(pos_act).owner != 0 and (cell(pos_act).type != Wall and cell(pos_act).id != -1 and unit(cell(pos_act).id).player != 0 and unit(cell(pos_act).id).type == Knight)){

      distancias[pos_act.i][pos_act.j] += 1;
      pos_desti = pos_act;
    int dist = distancias[pos_act.i][pos_act.j];
      return dist;
   }
    else if(cell(pos_act).type == Wall or (cell(pos_act).id != -1 and unit(cell(pos_act).id).player == 0)){

      edges.pop();
    }
   else{

    edges.pop();
  if(tablero[pos_act.i+1][pos_act.j] == false){
    distancias[pos_act.i+1][pos_act.j] = distancias[pos_act.i][pos_act.j] + 1;
    tablero[pos_act.i+1][pos_act.j] = true;
    edges.push(Pos(pos_act.i+1, pos_act.j));
  }
  if(tablero[pos_act.i-1][pos_act.j] == false){
    distancias[pos_act.i-1][pos_act.j] = distancias[pos_act.i][pos_act.j] + 1;
    tablero[pos_act.i-1][pos_act.j] = true;
    edges.push(Pos(pos_act.i-1, pos_act.j));
  }
  if(tablero[pos_act.i][pos_act.j+1] == false){
    distancias[pos_act.i][pos_act.j+1] = distancias[pos_act.i][pos_act.j] + 1;
    tablero[pos_act.i][pos_act.j+1] = true;
    edges.push(Pos(pos_act.i, pos_act.j+1));
  }
  if(tablero[pos_act.i][pos_act.j-1] == false){
    distancias[pos_act.i][pos_act.j-1] = distancias[pos_act.i][pos_act.j] + 1;
    tablero[pos_act.i][pos_act.j-1] = true;
    edges.push(Pos(pos_act.i, pos_act.j-1));
  }
   }
  }
  return 2000;
  
}

int busca_any_k(VBB tablero, VII distancias, queue<Pos> edges){
  
  while(edges.empty() == false){
    Pos pos_act = edges.front();
    if(cell(pos_act).type != Wall and cell(pos_act).id != -1 and unit(cell(pos_act).id).player != 0 and cell(pos_act).haunted == false and (unit(cell(pos_act).id).type == Farmer or unit(cell(pos_act).id).type == Knight)){

      distancias[pos_act.i][pos_act.j] += 1;
      return distancias[pos_act.i][pos_act.j];
   }
    else if(cell(pos_act).type == Wall or cell(pos_act).id != -1 or cell(pos_act).haunted){

      edges.pop();
    }
   else{

    edges.pop();
  if(tablero[pos_act.i+1][pos_act.j] == false){
    distancias[pos_act.i+1][pos_act.j] = distancias[pos_act.i][pos_act.j] + 1;
    tablero[pos_act.i+1][pos_act.j] = true;
    edges.push(Pos(pos_act.i+1, pos_act.j));
  }
  if(tablero[pos_act.i-1][pos_act.j] == false){
    distancias[pos_act.i-1][pos_act.j] = distancias[pos_act.i][pos_act.j] + 1;
    tablero[pos_act.i-1][pos_act.j] = true;
    edges.push(Pos(pos_act.i-1, pos_act.j));
  }
  if(tablero[pos_act.i][pos_act.j+1] == false){
    distancias[pos_act.i][pos_act.j+1] = distancias[pos_act.i][pos_act.j] + 1;
    tablero[pos_act.i][pos_act.j+1] = true;
    edges.push(Pos(pos_act.i, pos_act.j+1));
  }
  if(tablero[pos_act.i][pos_act.j-1] == false){
    distancias[pos_act.i][pos_act.j-1] = distancias[pos_act.i][pos_act.j] + 1;
    tablero[pos_act.i][pos_act.j-1] = true;
    edges.push(Pos(pos_act.i, pos_act.j-1));
  }
  if(tablero[pos_act.i+1][pos_act.j+1] == false){
    distancias[pos_act.i+1][pos_act.j+1] = distancias[pos_act.i][pos_act.j] + 1;
    tablero[pos_act.i+1][pos_act.j+1] = true;
    edges.push(Pos(pos_act.i+1, pos_act.j+1));
  }
  if(tablero[pos_act.i+1][pos_act.j-1] == false){
    distancias[pos_act.i+1][pos_act.j-1] = distancias[pos_act.i][pos_act.j] + 1;
    tablero[pos_act.i+1][pos_act.j-1] = true;
    edges.push(Pos(pos_act.i+1, pos_act.j-1));
  }
  if(tablero[pos_act.i-1][pos_act.j+1] == false){
    distancias[pos_act.i-1][pos_act.j+1] = distancias[pos_act.i][pos_act.j] + 1;
    tablero[pos_act.i-1][pos_act.j+1] = true;
    edges.push(Pos(pos_act.i-1, pos_act.j+1));
  }
  if(tablero[pos_act.i-1][pos_act.j-1] == false){
    distancias[pos_act.i-1][pos_act.j-1] = distancias[pos_act.i][pos_act.j] + 1;
    tablero[pos_act.i-1][pos_act.j-1] = true;
    edges.push(Pos(pos_act.i-1, pos_act.j-1));
  }

   }
  }
  return 2000;
}

int dir_val_k(Pos position){

  queue<Pos> edges0, edges1, edges2, edges3, edges4, edges5, edges6, edges7;
  Pos p0, p1, p2, p3, p4, p5, p6, p7;
  VBB tablero(37, VB(37,false));
  VII distancias(37, VI(37,-1));
  tablero[position.i][position.j] = true;
  p0 = Pos(position.i+1, position.j);
  p1 = Pos(position.i+1, position.j+1);
  p2 = Pos(position.i, position.j+1);
  p3 = Pos(position.i-1, position.j+1);
  p4 = Pos(position.i-1, position.j);
  p5 = Pos(position.i-1, position.j-1);
  p6 = Pos(position.i, position.j-1);
  p7 = Pos(position.i+1, position.j-1);
  edges0.push(p0); edges1.push(p1); edges2.push(p2); edges3.push(p3); edges4.push(p4); edges5.push(p5); edges6.push(p6); edges7.push(p7);
  int d0 = 2000, d1 = 2000, d2 = 2000, d3 = 2000, d4 = 2000, d5 = 2000, d6 = 2000, d7 = 2000;

  d1 = busca_any_k(tablero, distancias, edges1);
  d2 = busca_any_k(tablero, distancias, edges2);
  d3 = busca_any_k(tablero, distancias, edges3);
  d4 = busca_any_k(tablero, distancias, edges4);
  d0 = busca_any_k(tablero, distancias, edges0);
  d5 = busca_any_k(tablero, distancias, edges5);
  d6 = busca_any_k(tablero, distancias, edges6);

  d7 = busca_any_k(tablero, distancias, edges7);

  if(d0 != 2000 and d0<=d2 and d0<=d3 and d0<=d4 and d0<=d1 and d0<=d5 and d0<=d6 and d0<=d7) return 0;
  else if(d1 != 2000 and d1<=d2 and d1<=d3 and d1<=d4 and d1<=d0 and d1<=d5 and d1<=d6 and d1<=d7) return 1;
  else if(d2 != 2000 and d2<=d1 and d2<=d3 and d2<=d4 and d2<=d0 and d2<=d5 and d2<=d6 and d2<=d7) return 2;
  else if(d3 != 2000 and d3<=d2 and d3<=d1 and d3<=d4 and d3<=d0 and d3<=d5 and d3<=d6 and d3<=d7) return 3;
  else if(d4 != 2000 and d4<=d2 and d4<=d1 and d4<=d3 and d4<=d0 and d4<=d5 and d4<=d6 and d4<=d7) return 4;
  else if(d5 != 2000 and d5<=d2 and d5<=d1 and d5<=d4 and d5<=d0 and d5<=d3 and d5<=d6 and d5<=d7) return 5;
  else if(d6 != 2000 and d6<=d2 and d6<=d1 and d6<=d4 and d6<=d0 and d6<=d5 and d6<=d3 and d6<=d7) return 6;
  else if(d7 != 2000 and d7<=d2 and d7<=d1 and d7<=d4 and d7<=d0 and d7<=d5 and d7<=d6 and d7<=d3) return 7;
  else return 8;
}

int busca_any_f(VBB tablero, VII distancias, queue<Pos> edges, Pos &p1, VBB &celdas_f){  ///// BFS
  
 
 while(edges.empty() == false){
  Pos pos_act = edges.front();
  if(celdas_f[pos_act.i][pos_act.j] == 0 and(cell(pos_act).type != Wall and cell(pos_act).id == -1 and cell(pos_act).owner != 0 and cell(pos_act).haunted == false)){
      distancias[pos_act.i][pos_act.j] += 1;
      int dist = distancias[pos_act.i][pos_act.j];
      p1 = pos_act; 
      return dist;
  }
  else if(cell(pos_act).type == Wall or cell(pos_act).id != -1 or cell(pos_act).haunted){
    edges.pop();
  }
  else{
   
    edges.pop();
  if(tablero[pos_act.i+1][pos_act.j] == false){
    distancias[pos_act.i+1][pos_act.j] = distancias[pos_act.i][pos_act.j] + 1;
    tablero[pos_act.i+1][pos_act.j] = true;
    edges.push(Pos(pos_act.i+1, pos_act.j));
  }
  if(tablero[pos_act.i-1][pos_act.j] == false){
    distancias[pos_act.i-1][pos_act.j] = distancias[pos_act.i][pos_act.j] + 1;
    tablero[pos_act.i-1][pos_act.j] = true;
    edges.push(Pos(pos_act.i-1, pos_act.j));
  }
  if(tablero[pos_act.i][pos_act.j+1] == false){
    distancias[pos_act.i][pos_act.j+1] = distancias[pos_act.i][pos_act.j] + 1;
    tablero[pos_act.i][pos_act.j+1] = true;
    edges.push(Pos(pos_act.i, pos_act.j+1));
  }
  if(tablero[pos_act.i][pos_act.j-1] == false){
    distancias[pos_act.i][pos_act.j-1] = distancias[pos_act.i][pos_act.j] + 1;
    tablero[pos_act.i][pos_act.j-1] = true;
    edges.push(Pos(pos_act.i, pos_act.j-1));
  }
  }
 }
  return 2000;
}

int dir_val_farm_1(Pos position, VBB &celdas_f){
  /* Retorna la mejor direccion a la que tenemos que mover la tropa*/
  
  queue<Pos> edges1, edges2, edges3, edges4;
  Pos p1,p2,p3,p4;
  VBB tablero(37, VB(37,false));
  VII distancias(37, VI(37,-1));
  tablero[position.i][position.j] = true;
  p1 = Pos(position.i+1, position.j);
  p2 = Pos(position.i, position.j+1);
  p3 = Pos(position.i-1, position.j);
  p4 = Pos(position.i, position.j-1);
  edges1.push(p1); edges2.push(p2); edges3.push(p3); edges4.push(p4);
  int d1 = 2000 , d2 = 2000, d3 = 2000, d4 = 2000;

  d1 = busca_any_f(tablero, distancias, edges1, p1, celdas_f);

  d2 = busca_any_f(tablero, distancias, edges2, p2, celdas_f);

  d3 = busca_any_f(tablero, distancias, edges3, p3, celdas_f);
  
  d4 = busca_any_f(tablero, distancias, edges4, p4, celdas_f);

  if(d1 != 2000 and d1<=d2 and d1<=d3 and d1<=d4) {celdas_f[p1.i][p1.j] = 1; return 0;}
  else if(d2 != 2000 and d2<=d1 and d2<=d3 and d2<=d4) {celdas_f[p2.i][p2.j] = 1; return 2;}
  else if(d3 != 2000 and d3<=d2 and d3<=d1 and d3<=d4) {celdas_f[p3.i][p3.j] = 1; return 4;}
  else if(d4 != 2000 and d4<=d2 and d4<=d3 and d4<=d1) {celdas_f[p4.i][p4.j] = 1; return 6;}
  else return 8;
}

int dir_val_w(Pos position, VBB &celdas_w, int num){
  
  queue<Pos> edges1, edges2, edges3, edges4;
  Pos p1,p2,p3,p4;
  VBB tablero(37, VB(37,false));
  VII distancias(37, VI(37,-1));
  tablero[position.i][position.j] = true;

  p1 = Pos(position.i+1, position.j);
  p2 = Pos(position.i, position.j+1);
  p3 = Pos(position.i-1, position.j);
  p4 = Pos(position.i, position.j-1);
  edges1.push(p1); edges2.push(p2); edges3.push(p3); edges4.push(p4);
  int d1 = 2000 , d2 = 2000, d3 = 2000, d4 = 2000;

  d1 = busca_any_w(tablero, distancias, edges1, p1, celdas_w);
  d2 = busca_any_w(tablero, distancias, edges2, p2, celdas_w);
  d3 = busca_any_w(tablero, distancias, edges3, p3, celdas_w);
  d4 = busca_any_w(tablero, distancias, edges4, p4, celdas_w);
  if(num == 1){
    if(d1 != 2000 and d1<=d2 and d1<=d3 and d1<=d4) {celdas_w[p1.i][p1.j] = true ; return 0;}
    else if(d2 != 2000 and d2<=d1 and d2<=d3 and d2<=d4) {celdas_w[p2.i][p2.j] = true ; return 2;}
    else if(d3 != 2000 and d3<=d2 and d3<=d1 and d3<=d4) {celdas_w[p3.i][p3.j] = true ; return 4;}
    else if(d4 != 2000 and d4<=d2 and d4<=d3 and d4<=d1) {celdas_w[p4.i][p4.j] = true ; return 6;}
    else return 8;
  }
  else if(num == 2){
    if(d3 != 2000 and d3<=d2 and d3<=d1 and d3<=d4) {celdas_w[p3.i][p3.j] = true ; return 4;}
    else if(d4 != 2000 and d4<=d2 and d4<=d3 and d4<=d1) {celdas_w[p4.i][p4.j] = true ; return 6;}
    else if(d2 != 2000 and d2<=d1 and d2<=d3 and d2<=d4) {celdas_w[p2.i][p2.j] = true ; return 2;}
    else if(d1 != 2000 and d1<=d2 and d1<=d3 and d1<=d4) {celdas_w[p1.i][p1.j] = true ; return 0;}
    else return 8;

  }
 else return 8; /// esto lo pongo para que no salte un warning
}
  
  
void play(){

VI far = farmers(0);
VI knt = knights(0);
VI wit = witches(0);
VBB celdas_f(37, VB(37, 0));
//MOVIMIENTO DE LOS FARMERS

for(int farm : far){
  Pos POS_F = unit(farm).pos;  
  command(farm, Dir(dir_val_farm_1(POS_F, celdas_f)));
  
  }

// MOVIMIENTO DE LOS KNIGHTS

for(int kni : knt){
  Pos POS_K = unit(kni).pos;
  command(kni, Dir(dir_val_k(POS_K)));
 }

//MOVIMIENTO DE LAS BRUJAS
if(round() <=7){
  VI w = witches(0);
  int bruja1 = w[0];
  int bruja2 = w[1];
  int diferencia_i, diferencia_j;
  Pos pos1 = unit(bruja1).pos;
  Pos pos2 = unit(bruja2).pos;

  if(pos1.j <= pos2.j){
    diferencia_j = pos2.j - pos1.j;
    if(pos1.i <= pos2.i){

      diferencia_i = pos2.i - pos1.i;
      if(diferencia_i >= diferencia_j){
        command(bruja1, Dir(2));
        command(bruja2, Dir(0));
      }
      else{
        command(bruja1, Dir(0));
        command(bruja2, Dir(2));
      }
    }
    else{
      command(bruja1, Dir(0));
      command(bruja2, Dir(2));
    }
  }
 
  else {
      diferencia_j = pos1.j- pos2.j;
      if(pos1.i >= pos2.i){
        diferencia_i = pos1.i - pos2.i;
        if(diferencia_i >= diferencia_j){
          command(bruja1, Dir(0));
          command(bruja2, Dir(2));
        }
        else{
          command(bruja1, Dir(2));
          command(bruja2, Dir(0));
        }
      }
      else {
        command(bruja1, Dir(2));
      command(bruja2, Dir(0));
      }
  }
}
  
else if(round() >7){
  VBB celdas_w(37, VB(37, 0));
  VI w = witches(0);
  int bruja1 = w[0];
  int bruja2 = w[1];
  Pos pos1 = unit(bruja1).pos;
  Pos pos2 = unit(bruja2).pos;
  command(bruja1, Dir(dir_val_w(pos1, celdas_w,1)));
  command(bruja2, Dir(dir_val_w(pos2, celdas_w,2)));
}

}
};
RegisterPlayer(PLAYER_NAME);