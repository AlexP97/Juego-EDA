Dir direccio_f(Pos old_pos, Pos new_pos) {
    int x = new_pos.i - old_pos.i;
    int y = new_pos.j - old_pos.j;
    if(y != 0) {
      if(y > 0) 
	  return Right;
	
      if(y < 0)
	return Left;
    }
    if(x != 0) {
      if(x > 0)
	return Bottom;
      if(x < 0)
	return Top;
    }
    return None;
  }

















struct Pos_i_dist {
    Pos pos;
    int dist = 0;
  };
  
  int distancia_entre_dos_cells(int x1, int y1, int x2, int y2) {
    queue<Pos_i_dist> p;
    bool trobat = false;
    Pos_i_dist aux;
    aux.pos.i = x1;
    aux.pos.j = y1;
    p.push(aux);
    Pos_i_dist ps;
    while(not p.empty() && not trobat) {
      ps = p.front();
      p.pop();
      if(ps.pos.i == x2 && ps.pos.j == y2) 
	trobat = true;
      if(posicio_valida_f(ps.pos.i+1,ps.pos.j)) {
	aux.pos.i = ps.pos.i+1;
	aux.pos.j = ps.pos.j;
	aux.dist = ps.dist+1;
	p.push(aux);
      }
      if(posicio_valida_f(ps.pos.i-1,ps.pos.j)) {
	aux.pos.i = ps.pos.i-1;
	aux.pos.j = ps.pos.j;
	aux.dist = ps.dist+1;
	p.push(aux);
      }
      if(posicio_valida_f(ps.pos.i,ps.pos.j+1)) {
	aux.pos.i = ps.pos.i;
	aux.pos.j = ps.pos.j+1;
	aux.dist = ps.dist+1;
	p.push(aux);
      }
		
      if(posicio_valida_f(ps.pos.i,ps.pos.j-1)) {
	aux.pos.i = ps.pos.i;
	aux.pos.j = ps.pos.j-1;
	aux.dist = ps.dist+1;
	p.push(aux);	
      }	
    }
    if(trobat) return ps.dist;
    else return -1;
  }




  int distancia_entre_dos_cells(int xold, int yold, int xnew, int ynew) {
    if(posicio_valida_f(xold,yold)) {
      queue<Pos> p;
      queue<distancia> d;
      bool esta = false;
      distancia aux;
      aux.dist = 0;
      d.push(aux);
      p.push({xold,yold});
      Pos pos;
      distancia dt;
      while(not p.empty() && not esta) {
	dt = d.front();
	pos = p.front();
	p.pop();
	d.pop();
	if(pos.i == xnew && pos.j == ynew)  
	  esta = true;
	if(posicio_valida_f(pos.i+1,pos.j)) {
	  aux.dist = dt.dist++;
	  d.push(aux);
	  p.push({pos.i+1,pos.j});
	}
	if(posicio_valida_f(pos.i-1,pos.j)) {
	  aux.dist = dt.dist++;
	  d.push(aux);
	  p.push({pos.i-1,pos.j});
	}
	if(posicio_valida_f(pos.i,pos.j+1)) {
	  aux.dist = dt.dist++;
	  d.push(aux);
	  p.push({pos.i,pos.j+1});
	}
		
	if(posicio_valida_f(pos.i,pos.j-1)) {
	  aux.dist = dt.dist++;
	  d.push(aux);
	  p.push({pos.i,pos.j-1});	
	}		
      }
      if(esta) 
	return dt.dist;
    }
    return -1;
  }
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  Pos moviment_k(int x, int y) {
    queue<Cell> q;
    queue<Pos> p;
    bool trobat = false;
    q.push(cell(x,y));
    p.push({x,y});
    Cell cact;
    Pos pos;
    while(not q.empty() && not trobat) {
      cact = q.front();
      pos = p.front();
      p.pop();
      q.pop();
      if(cact.id != -1 && unit(cact.id).player != 0) 
	trobat = true;
      if(posicio_valida_f(pos.i+1,pos.j+1)) {
	q.push(cell(pos.i+1,pos.j+1));
	p.push({pos.i+1,pos.j+1});
      }
      if(posicio_valida_f(pos.i-1,pos.j-1)) {
	q.push(cell(pos.i-1,pos.j-1));
	p.push({pos.i-1,pos.j-1});
      }
      if(posicio_valida_f(pos.i-1,pos.j+1)) {
	q.push(cell(pos.i-1,pos.j+1));
	p.push({pos.i-1,pos.j+1});
      }
		
      if(posicio_valida_f(pos.i+1,pos.j-1)) {
	q.push(cell(pos.i+1,pos.j-1));
	p.push({pos.i+1,pos.j-1});	
      }		
      if(posicio_valida_f(pos.i+1,pos.j)) {
	q.push(cell(pos.i+1,pos.j));
	p.push({pos.i+1,pos.j});
      }
      if(posicio_valida_f(pos.i-1,pos.j)) {
	q.push(cell(pos.i-1,pos.j));
	p.push({pos.i-1,pos.j});
      }
      if(posicio_valida_f(pos.i,pos.j+1)) {
	q.push(cell(pos.i,pos.j+1));
	p.push({pos.i,pos.j+1});
      }
		
      if(posicio_valida_f(pos.i,pos.j-1)) {
	q.push(cell(pos.i,pos.j-1));
	p.push({pos.i,pos.j-1});	
      }		
    }
    if(trobat) 
      return pos;
    else 
      return {-1,-1};	
  }
  
  Dir direccio_k(Pos old_pos, Pos new_pos) {
    int x = new_pos.i - old_pos.i;
    int y = new_pos.j - old_pos.j;
    if(x != 0 && y != 0) {
     if(x < 0 && y < 0) 
       return TL;
     if(x > 0 && y > 0)
       return BR;
     if(x > 0 && y < 0)
       return LB;
     if(x < 0 && y > 0)
       return RT;
    }
    if(y != 0) {
      if(y > 0) 
	  return Right;
      if(y < 0)
	return Left;
    }
    if(x != 0) {
      if(x > 0)
	return Bottom;
      if(x < 0)
	return Top;
    }
    return None;
  }
  
  
  
  
   Pos moviment_k(int x, int y) {
    queue<Cell> q;
    queue<Pos> p;
    Mvis m(37, vector<bool> (37,false));
    bool trobat = false;
    q.push(cell(x,y));
    p.push({x,y});
    Cell cact;
    Pos pos;
    while(not q.empty() && not trobat) {
      cact = q.front();
      pos = p.front();
      q.pop();
      p.pop();
      m[pos.i][pos.j] = true;
      int id2 = cact.id;
      if(id2 != -1) {
	Unit u = unit(id2);
	if(u.player != 0)  
	  trobat = true;
      }
      if(posicio_valida_k((pos.i+1),pos.j) && not m[(pos.i+1)][pos.j]) {
	q.push(cell((pos.i+1),pos.j));
	p.push({(pos.i+1),pos.j});
      }
      if(posicio_valida_k((pos.i-1),pos.j) && not m[(pos.i-1)][pos.j]) {
	q.push(cell((pos.i-1),pos.j));
	p.push({(pos.i-1),pos.j});
      }
      if(posicio_valida_k(pos.i,(pos.j+1)) && not m[pos.i][(pos.j+1)]) {
	q.push(cell(pos.i,(pos.j+1)));
	p.push({pos.i,(pos.j+1)});
      }
		
      if(posicio_valida_k(pos.i,(pos.j-1)) && not m[pos.i][(pos.j-1)]) {
	q.push(cell(pos.i,(pos.j-1)));
	p.push({pos.i,(pos.j-1)});	
      }		
      if(posicio_valida_k((pos.i+1),pos.j+1) && not m[(pos.i+1)][pos.j+1]) {
	q.push(cell((pos.i+1),pos.j+1));
	p.push({(pos.i+1),pos.j+1});
      }
      if(posicio_valida_k((pos.i-1),pos.j-1) && not m[(pos.i-1)][pos.j-1]) {
	q.push(cell((pos.i-1),pos.j-1));
	p.push({(pos.i-1),pos.j-1});
      }
      if(posicio_valida_k(pos.i-1,(pos.j+1)) && not m[pos.i-1][(pos.j+1)]) {
	q.push(cell(pos.i-1,(pos.j+1)));
	p.push({pos.i-1,(pos.j+1)});
      }
		
      if(posicio_valida_k(pos.i+1,(pos.j-1)) && not m[pos.i+1][(pos.j-1)]) {
	q.push(cell(pos.i+1,(pos.j-1)));
	p.push({pos.i+1,(pos.j-1)});	
      }		
    }
    if(trobat) 
      return pos;
    else 
      return {-1,-1};
		
  }
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  bool aliat = false;
    vector<int> is = {1,2,1,1,0,0,0,0,-1,-1,-1,-2};
    vector<int> js = {0,0,1,-1,1,2,-1,-2,1,-1,0,0};
    for(int k = 0; k < 12 and not aliat; k++) {
      if(cell(i+is[k],j+js[k]).id != -1 && m[i+is[k]][j+js[k]]) aliat = true;
    }
    if(aliat) return false;
    
    
    
    
    
    
    
    
    
    
    
    