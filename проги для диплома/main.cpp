int pointCounter = 1;

class StringHelper{
  
  public:

  char * string;
  int     mLength;
  
  StringHelper(){
    string = 0;
    mLength = 0;
  }

  boolean strEquals(char * str2){

    if (mLength == 0 )
      return false;
    
    for (int i = 0; i < mLength; i++){
      {   
        if (string[i] != str2[i])
        return false;
      }

      
    }

    return true;
  }

  void flush(){

    if (mLength != 0)
    {
      delete [] string;
    }
    mLength = 0;
  }

  void readFromSerial(int length){
    
    char pos = 0;      
 
    if (Serial.available() > 0) {

               if (mLength != 0)
            {
              flush();
              string = new char[length + 1];
             }
             else 
             string = new char[length + 1];

             mLength = length + 1;

      while (Serial.available() > 0) {

          if (pos == mLength){     
             Serial.flush();
              break;
            }
                
                string[pos++] = Serial.read();
              
            }
         string[length] = '\0';
        }
  }
  
};

StringHelper strHelper;

void setup(){
  Serial.begin(57600);
  randomSeed(analogRead(0));
}

void loop(){
  
    strHelper.readFromSerial(1);

  if (strHelper.strEquals("A"))
    {
      Serial.write(static_cast<char*>(static_cast<void*>(&pointCounter)),4);
      long val = random(2048);
      Serial.write(static_cast<char*>(static_cast<void*>(&val)),8);
      pointCounter += 1;
    }
    else
    if (strHelper.strEquals("V")){
      Serial.write("Version 0.0.1");
      pointCounter++;
    }

    Serial.flush();
    
    strHelper.flush();
    
   delay(5);
}

/*
int main(){

while(true){



}
}
