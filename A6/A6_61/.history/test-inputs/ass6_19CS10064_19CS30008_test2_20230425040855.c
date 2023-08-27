int printInt(int num);
int printStr(char * c);
int readInt(int *eP);


int main()
{
   int x = 2;
   int y = 3;
   int z = 1;
   int m;
   if(x > y) m = x;
   else m = y;
   if(m > z) m = m;
   else m = z;
   printStr("max(");
   printInt(x); printStr(" ");
   printInt(y); printStr(" ");
   printInt(z); printStr(") = ");
   printInt(m);
   
}