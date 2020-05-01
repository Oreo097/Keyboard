/*这是前期实验Arduino算法，主要用于扫描算法的检查*/

#define LED 2

#define Row1 3
#define Row2 4

#define Col1 5
#define Col2 6
#define Col3 7
#define Col4 8
#define Col5 9
#define Col6 10

void setup()
{
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);
  pinMode(Row1, INPUT);
  pinMode(Row2, INPUT);

  pinMode(Col1, OUTPUT);
  pinMode(Col2, OUTPUT);
  pinMode(Col3, OUTPUT);
  pinMode(Col4, OUTPUT);
  pinMode(Col5, OUTPUT);
  delay(500);
  digitalWrite(LED, LOW);
  Serial.begin(9600);
  delay(500);
}

void loop()
{
  struct matrix
  {
    int key[12] = {0};
    int *inter = key;
  } matrix;
  digitalWrite(LED, HIGH);
  digitalWrite(Col1, HIGH);
  digitalWrite(Col2, LOW);
  digitalWrite(Col3, LOW);
  digitalWrite(Col4, LOW);
  digitalWrite(Col5, LOW);
  digitalWrite(Col6, LOW);
  delay(1); //延迟1ms使电平平稳
  if (digitalRead(Row1) == HIGH)
  {
    *matrix.inter = 1;
    matrix.inter++;
  }
  if (digitalRead(Row2) == HIGH)
  {
    *matrix.inter = 1;
    matrix.inter++;
  }

  digitalWrite(Col1, LOW);
  digitalWrite(Col2, HIGH);
  digitalWrite(Col3, LOW);
  digitalWrite(Col4, LOW);
  digitalWrite(Col5, LOW);
  digitalWrite(Col6, LOW);
  delay(1); //延迟1ms使电平平稳
  if (digitalRead(Row1) == HIGH)
  {
    *matrix.inter = 1;
    matrix.inter++;
  }
  if (digitalRead(Row2) == HIGH)
  {
    *matrix.inter = 1;
    matrix.inter++;
  }
  digitalWrite(Col1, LOW);
  digitalWrite(Col2, LOW);
  digitalWrite(Col3, HIGH);
  digitalWrite(Col4, LOW);
  digitalWrite(Col5, LOW);
  digitalWrite(Col6, LOW);
  delay(1); //延迟1ms使电平平稳
  if (digitalRead(Row1) == HIGH)
  {
    *matrix.inter = 1;
    matrix.inter++;
  }
  if (digitalRead(Row2) == HIGH)
  {
    *matrix.inter = 1;
    matrix.inter++;
  }
  digitalWrite(Col1, LOW);
  digitalWrite(Col2, LOW);
  digitalWrite(Col3, LOW);
  digitalWrite(Col4, HIGH);
  digitalWrite(Col5, LOW);
  digitalWrite(Col6, LOW);
  delay(1); //延迟1ms使电平平稳
  if (digitalRead(Row1) == HIGH)
  {
    *matrix.inter = 1;
    matrix.inter++;
  }
  if (digitalRead(Row2) == HIGH)
  {
    *matrix.inter = 1;
    matrix.inter++;
  }
  digitalWrite(Col1, LOW);
  digitalWrite(Col2, LOW);
  digitalWrite(Col3, LOW);
  digitalWrite(Col4, LOW);
  digitalWrite(Col5, HIGH);
  digitalWrite(Col6, LOW);
  delay(1); //延迟1ms使电平平稳
  if (digitalRead(Row1) == HIGH)
  {
    *matrix.inter = 1;
    matrix.inter++;
  }
  if (digitalRead(Row2) == HIGH)
  {
    *matrix.inter = 1;
    matrix.inter++;
  }
  digitalWrite(Col1, LOW);
  digitalWrite(Col2, LOW);
  digitalWrite(Col3, LOW);
  digitalWrite(Col4, LOW);
  digitalWrite(Col5, LOW);
  digitalWrite(Col6, HIGH);
  delay(1); //延迟1ms使电平平稳
  if (digitalRead(Row1) == HIGH)
  {
    *matrix.inter = 1;
    matrix.inter++;
  }
  if (digitalRead(Row2) == HIGH)
  {
    *matrix.inter = 1;
    matrix.inter++;
  }
  for (int i = 0; i < 12; i++)
  {
    Serial.println(matrix.key[i]);
    delay(2);
  }
  delay(500);
}
