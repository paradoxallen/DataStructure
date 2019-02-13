bool Insert( List L, ElementType X ){

  if(L->Last+1 == MAXSIZE){
    return false;
  }
      
  for(int i=0; i<=L->Last; i++){
    if(X==L->Data[i]){
      return false;
    }
    else if(X>L->Data[i]){
      for(int j=L->Last; j>=i; j--){
        L->Data[j+1] = L->Data[j];
      }
      L->Data[i] = X;
      L->Last++;
      break;
    }
    else if(X<L->Data[i]&&i==L->Last){
      L->Data[L->Last+1]=X;
      L->Last++;
      break;
    }
  }
  return true;
}

