// An example of how you could make a 7 segment display, display different numbers

static int A = 13;
static int B = 11;
static int C = 8;
static int D = 9;
static int E = 7;
static int F = 12;
static int G = 10;
static int DP = 6;
    
void setNumber(int n);
    
void setup()
{
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);      
}
    
 void loop()
 {
  for (int i = 9; i > 0; i--)
  {
    setNumber(i);
    delay (500);
  }
  delay(2000);
 }
 
 
 
 void setNumber(int n)
 {
   switch (n)
   {
     case 0:
     {
       digitalWrite(A, LOW);
       digitalWrite(B, LOW);
       digitalWrite(C, LOW);
       digitalWrite(D, LOW);
       digitalWrite(E, LOW);
       digitalWrite(F, LOW);
       digitalWrite(G, HIGH);
       digitalWrite(DP, HIGH);
       break;
     }
     case 1:
     {
       digitalWrite(A, HIGH);
       digitalWrite(B, LOW);
       digitalWrite(C, LOW);
       digitalWrite(D, HIGH);
       digitalWrite(E, HIGH);
       digitalWrite(F, HIGH);
       digitalWrite(G, HIGH);
       digitalWrite(DP, HIGH);
       break;
     }
     case 2:
     {
       digitalWrite(A, LOW);
       digitalWrite(B, LOW);
       digitalWrite(C, HIGH);
       digitalWrite(D, LOW);
       digitalWrite(E, LOW);
       digitalWrite(F, HIGH);
       digitalWrite(G, LOW);
       digitalWrite(DP, HIGH);
       break;
     }
     case 3:
     {
       digitalWrite(A, LOW);
       digitalWrite(B, LOW);
       digitalWrite(C, LOW);
       digitalWrite(D, LOW);
       digitalWrite(E, HIGH);
       digitalWrite(F, HIGH);
       digitalWrite(G, LOW);
       digitalWrite(DP, HIGH);
       break;
     }
     case 4:
     {
       digitalWrite(A, HIGH);
       digitalWrite(B, LOW);
       digitalWrite(C, LOW);
       digitalWrite(D, HIGH);
       digitalWrite(E, HIGH);
       digitalWrite(F, LOW);
       digitalWrite(G, LOW);
       digitalWrite(DP, HIGH);
       break;
     }
     case 5:
     {
       digitalWrite(A, LOW);
       digitalWrite(B, HIGH);
       digitalWrite(C, LOW);
       digitalWrite(D, LOW);
       digitalWrite(E, HIGH);
       digitalWrite(F, LOW);
       digitalWrite(G, LOW);
       digitalWrite(DP, HIGH);
       break;
     }
     case 6:
     {
       digitalWrite(A, LOW);
       digitalWrite(B, HIGH);
       digitalWrite(C, LOW);
       digitalWrite(D, LOW);
       digitalWrite(E, LOW);
       digitalWrite(F, LOW);
       digitalWrite(G, LOW);
       digitalWrite(DP, HIGH);
       break;
     }
     case 7:
     {
       digitalWrite(A, LOW);
       digitalWrite(B, LOW);
       digitalWrite(C, LOW);
       digitalWrite(D, HIGH);
       digitalWrite(E, HIGH);
       digitalWrite(F, LOW);
       digitalWrite(G, HIGH);
       digitalWrite(DP, HIGH);
       break;
     }
     case 8:
     {
       digitalWrite(A, LOW);
       digitalWrite(B, LOW);
       digitalWrite(C, LOW);
       digitalWrite(D, LOW);
       digitalWrite(E, LOW);
       digitalWrite(F, LOW);
       digitalWrite(G, LOW);
       digitalWrite(DP, HIGH);
       break;
     }
     case 9:
     {
       digitalWrite(A, LOW);
       digitalWrite(B, LOW);
       digitalWrite(C, LOW);
       digitalWrite(D, LOW);
       digitalWrite(E, HIGH);
       digitalWrite(F, LOW);
       digitalWrite(G, LOW);
       digitalWrite(DP, HIGH);
       break;
     }
   }
 }

