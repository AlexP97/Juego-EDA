#include "Player.hh"
#include <limits>


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME ru_6


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
  struct index {
    bool v;
    int d;
    Dir mov;
  };
  
  typedef vector<int> VE;
  typedef vector<VE> VVE;
  typedef vector<index> VB;
  typedef vector<VB> VVB;
  
  bool es_ok_f(Pos p, bool primer) {
    Cell c = cell(p);
    return ( (primer and c.type ==  Empty and c.id == -1 and not c.haunted) or (not primer and c.type ==  Empty and not c.haunted));
  }
  
    bool es_ok_k(Pos p,  Unit m_a,  bool& enemic) {
    Cell c = cell(p);
    if (c.id != -1) {
      Unit m = unit(c.id);
      enemic = true;
      return (c.type ==  Empty and m.player !=  0 and not c.haunted and m.type != Witch);
    }
    else return (c.type ==  Empty and not c.haunted);
  }
  
   bool es_ok_w(Pos p, bool& enemic) {
    Cell c = cell(p);
    if (c.id != -1) {
      Unit m = unit(c.id);
      enemic = true;
      return (c.type ==  Empty and m.player !=  0 and m.type == Knight );
    }
    else return (c.type ==  Empty);
  }
  
  
  Dir cerca_bfs_w(Pos a, VVE& marcats) {
    VVB vist(37, VB(37));
    for (int i = 0; i < 37; i++)
      for (int j = 0; j < 37; j++) 
	{ 
	  vist[i][j].v = false;
	  vist[i][j].d = numeric_limits<int>::max();
	  vist[i][j].mov = None;
	  
	}
    vist[a.i][a.j].v= true; vist[a.i][a.j].d = 0;
    queue<Pos> cua;
    cua.push(a);
    bool trobat = false;
    bool primer = true;
    bool enemic = false;
    
    VE direccions(4);
      for (int i = 0; i < 4; i++) 
	direccions[i] = (i*2);
      
    VE perm = random_permutation(4);
    
    while (not cua.empty() and not trobat) {
      Pos u = cua.front(); cua.pop();
      
      for (int it = 0; it < 4 and not trobat; it++) {
	Pos u_2 = u + Dir(perm[it]*2);
	if ( not trobat and es_ok_w(u_2, enemic) and not vist[u_2.i][u_2.j].v ) {
	  cua.push(u_2);
	  vist[u_2.i][u_2.j].v = true;
	  vist[u_2.i][u_2.j].d = vist[u.i][u.j].d + 1;
	  if (primer) vist[u_2.i][u_2.j].mov = Dir(perm[it]*2); 
	  else vist[u_2.i][u_2.j].mov = vist[u.i][u.j].mov;
	  if (enemic and marcats[u_2.i][u_2.j] != 1) { 
	    trobat = true; 
	    marcats[u_2.i][u_2.j] = 1; 
	  }
	}
      enemic = false;
	
      }
      primer = false; 
    }
    if (trobat) {
      Pos t = cua.back();
      return vist[t.i][t.j].mov;
    }
    return None;
  }
  
  Dir cerca_bfs_k(Pos a,  Unit m_a) {
    VVB vist(37, VB(37));
    for (int i = 0; i < 37; i++)
      for (int j = 0; j < 37; j++) 
	{ vist[i][j].v = false;
	  vist[i][j].d = numeric_limits<int>::max();
	  vist[i][j].mov = None;
	}
	
    vist[a.i][a.j].v= true;
    vist[a.i][a.j].d = 0;
    queue<Pos> cua;
    cua.push(a);
    bool trobat = false;
    bool primer = true;
    bool enemic = false;
    while (not cua.empty() and not trobat) {
      Pos u = cua.front(); cua.pop();
      VE perm = random_permutation(8);
      for (int it = 0; it < 8 and not trobat; it++) {
	Pos u_2 = u + Dir(perm[it]);
	if ( not trobat and es_ok_k(u_2,  m_a,  enemic) and not vist[u_2.i][u_2.j].v ) {
	  cua.push(u_2);
	  vist[u_2.i][u_2.j].v = true; vist[u_2.i][u_2.j].d = vist[u.i][u.j].d + 1;
	  if (primer) vist[u_2.i][u_2.j].mov = Dir(perm[it]); 
	  else vist[u_2.i][u_2.j].mov = vist[u.i][u.j].mov;
	  if (enemic) { trobat = true; }
	}
      enemic = false;
      }
      primer = false; 
    }
    
    if (trobat) {
      Pos t = cua.back();
      return vist[t.i][t.j].mov;
    }
    return None;
  }
  
  Dir cerca_bfs_f(Pos a, VVE& marcats) {
    VVB vist(37, VB(37));
    for (int i = 0; i < 37; i++)
      for (int j = 0; j < 37; j++) 
	{ 
	  vist[i][j].v = false;
	  vist[i][j].d = numeric_limits<int>::max();
	  vist[i][j].mov = None;}
    
    vist[a.i][a.j].v= true; vist[a.i][a.j].d = 0;
    queue<Pos> cua;
    cua.push(a);
    bool trobat = false;
    bool primer = true;
    VE direccions(4);
    for (int i = 0; i < 4; i++) 
	direccions[i] = (i*2);
      
    while (not cua.empty() and not trobat) {
      Pos u = cua.front(); cua.pop();
      
      for (int it = 0; it < 4 and not trobat; it++) {
	Pos u_2 = u + Dir(direccions[it]);
	if ( not trobat and es_ok_f(u_2, primer) and not vist[u_2.i][u_2.j].v ) {
	  cua.push(u_2);
	  vist[u_2.i][u_2.j].v = true; vist[u_2.i][u_2.j].d = vist[u.i][u.j].d + 1;
	  if (primer) vist[u_2.i][u_2.j].mov = Dir(direccions[it]); 
	  else vist[u_2.i][u_2.j].mov = vist[u.i][u.j].mov;
	  if (cell(u_2).owner != 0 and marcats[u_2.i][u_2.j] != 1) {
	    trobat = true; 
	    marcats[u_2.i][u_2.j] = 1; 
	    
	  }
	}
      }
      primer = false;
    }
    if (trobat) {
      Pos t = cua.back();
      return vist[t.i][t.j].mov;
    }
    return None;
  }
  
  /**
   * Play method, invoked once per each round.
   */
  
  virtual void play () {
    
    Pos actual;
    VVE marcats(37, VE(37, 0));
    VE f = farmers(0);
    for (int unsigned i = 0; i < f.size(); ++i) {
      actual = unit(f[i]).pos;
      Dir executar = cerca_bfs_f(actual, marcats);
      command(f[i], executar);
    }
    
    VE k = knights(0);
    for (int unsigned i = 0; i < k.size(); ++i) {
      actual = unit(k[i]).pos;
      Dir executar = cerca_bfs_k(actual,  unit(k[i]));
      command(k[i], executar);
    }
    
    marcats = VVE (37, VE(37, 0));
    VE w = witches(0);
    actual = unit(w[0]).pos;
    Dir executar = cerca_bfs_w(actual, marcats);
    command(w[0], executar);
    actual = unit(w[1]).pos;
    executar = cerca_bfs_w(actual, marcats);
    command(w[1], executar);
    
    
  }

};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
