int plus = A0;
int next = A1;
int start = A2;
int blinkPin = A3;
int KYS = A4;
int relayPinsArray[6] = { 2, 3, 4, 5, 6, 7 };
int relayTimesArray[6] = { 0, 0, 0, 0, 0, 0 };
int signLedsArray[6] = { 8, 9, 10, 11, 12, 13};
int tempRelay = 0;

void setup(){
    for(int i=A0; i<A3; i++){
        pinMode(i, INPUT);
        analogWrite(i, 10);
    }
    pinMode(blinkPin, OUTPUT);
    digitalWrite(blinkPin, LOW);
    pinMode(KYS, OUTPUT);
    digitalWrite(KYS, HIGH);
    for(int i=2; i<14; i++){
        pinMode(i, OUTPUT);
        digitalWrite(i, LOW);
    }
    Serial.begin(9600);
    Serial.println("Init complete!");
}

void loop(){
    Serial.print("Waiting for relay ");
    Serial.print(tempRelay+1);
    Serial.println();
    digitalWrite(relayPinsArray[tempRelay], HIGH);
    if (analogRead(plus)>100){
        if (relayTimesArray[tempRelay]>6) relayTimesArray[tempRelay] = 0;
        relayTimesArray[tempRelay]++;
        Serial.print("Time ++, tempTime: ");
        Serial.print(relayTimesArray[tempRelay]);
        Serial.println();
        sign(relayTimesArray[tempRelay], 0);
    } 
    if (analogRead(next)>100){
        blink(1,3);
        Serial.print("Relay set: ");
        Serial.print(tempRelay+1);
        Serial.print(": ");
        digitalWrite(relayPinsArray[tempRelay], LOW);
        Serial.print(relayTimesArray[tempRelay]);
        Serial.println();
        tempRelay++;
        if (tempRelay==6) tempRelay=0;
    }
    if (analogRead(start)>100){
        digitalWrite(relayTimesArray[tempRelay], LOW);
        Serial.println("Start!");
        blink(2, 5);
        tempRelay = 0;
        wait();
        blink(2, 5);
        digitalWrite(KYS, LOW);
        for (int i=0; i<6; i++) digitalWrite(relayPinsArray[i], LOW);
        while (true){
            Serial.println("Ended!");
            blink(1, 1);
        }
    }
}

void wait(){
    while (true){
        for (int i=0; i<6; i++) Serial.print(relayTimesArray[i]);
        for (int i=0; i<6; i++){
            if (relayTimesArray[i] != 0){
            digitalWrite(relayPinsArray[i], HIGH);
            }
        else {
            digitalWrite(relayPinsArray[i], LOW);
            }
        }
        if (listSum()==0) break;
        Serial.print("ListSum: ");
        Serial.print(listSum());
        Serial.println();
        waitMinutes(30);
        for (int i=0; i<6; i++){
            if (relayTimesArray[i] != 0) relayTimesArray[i]-=1;
        }
    }
}

int listSum(){
    int sum=0;
    for (int i=0; i<6; i++){
        sum += relayTimesArray[i];
    }
    return sum;
}

void waitMinutes(int value){
    for (int i=0; i<value; i++) delay(60000);
}

//signLedsArray
void sign(int number, int mode){
    if (number < 1 || number > 6) return;
    if (mode == 0){ //all the numbers till a given number
        for (int i=0; i<number; i++){
            digitalWrite(signLedsArray[i], HIGH);
        }
    }
    if (mode == 1){ //one given number out
        digitalWrite(signLedsArray[number+1], HIGH);
    }
    delay(2000);
    for (int i=0; i<6; i++){
        digitalWrite(signLedsArray[i], LOW);
    }
}

void blink(int sec, int times){
    int dt=(sec*1000)/times;
    for (int i=0; i<times; i++){
        digitalWrite(blinkPin, HIGH);
        delay(dt/2);
        digitalWrite(blinkPin, LOW);
        delay(dt/2);
    }
}