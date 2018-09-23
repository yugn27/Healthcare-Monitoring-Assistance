const int xpin=A2;
int ypin=A3;
int zpin=A4;

//int powerpin=A0;
//int gnd=A1;

float threshhold=40.0;

float xval[100]={0};
float yval[100]={0};
float zval[100]={0};
float xavg;
float yavg;
float zavg;
  
int steps,flag=0;
void setup()
{
Serial.begin(9600);
//pinMode(powerpin,OUTPUT);
//pinMode(gnd,OUTPUT);
//digitalWrite(powerpin,HIGH);
//digitalWrite(gnd,LOW);
pinMode(13,OUTPUT);
calibrate();
}

void loop()
{int acc=0;
  float totvect[100]={0};
float totave[100]={0};

  float xaccl[100]={0};
  float yaccl[100]={0};
  float zaccl[100]={0};
for (int i=0;i<100;i++)
{
xaccl[i]=float(analogRead(xpin));
delay(1);
yaccl[i]=float(analogRead(ypin));
delay(1);
zaccl[i]=float(analogRead(zpin));
delay(1);
 totvect[i] = sqrt(((xaccl[i]-xavg)* (xaccl[i]-xavg))+ ((yaccl[i] - yavg)*(yaccl[i] - yavg)) + ((zval[i] - zavg)*(zval[i] - zavg)));
 totave[i] = (totvect[i] + totvect[i-1]) / 2 ; 
 delay(200);
if (totave[i]>threshhold && flag==0)
{
  steps=steps+2;
  flag=1;
}
 else if (totave[i] > threshhold && flag==1)
{
}
  if (totave[i] <threshhold  && flag==1)
  {flag=0;}
  Serial.println(steps);
}
 delay(1000); 
}
void calibrate()
{
  digitalWrite(13,HIGH);
  float sum=0;
  float sum1=0;
  float sum2=0;
for (int i=0;i<100;i++)
{
xval[i]=float(analogRead(xpin));

sum=xval[i]+sum;
}
delay(100);
xavg=sum/100.0;
for (int j=0;j<100;j++)
{
xval[j]=float(analogRead(xpin));
sum1=xval[j]+sum1;
}
yavg=sum1/100.0;
delay(100);
for (int i=0;i<100;i++)
{
zval[i]=float(analogRead(zpin));
sum2=zval[i]+sum2;
}
zavg=sum2/100.0;
delay(100);
digitalWrite(13,LOW);
}

