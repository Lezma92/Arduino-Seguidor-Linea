class operaciones {
  private:
    int x = 1;//identifca el color de la linea
    int y = 0;//detecta el fondo de la linea
    int temp = 0;

    //Definicion de pines para sensores seguidores de linea
    const int sLnDer = 2;
    const int sLnIzq = 4;
    const int sLnCenter = 3;

    //definicion de pines para motores
    int izqA = 5;
    int izqB = 6;
    
    int derA = 9;
    int derB = 10;

    //definicion del puerto para el boton de encendido y apagado
    const int power = 9;

    //variable para el control de la velocidad
    int vel = 255;
    int velVuelta = 20;
    int t = 30;

    const int ledAtras = 8;

    const int btnEncender = 7;
    
    //banderas de estado para el manejo del desvio de los seguidores de linea
    int bDer = 0;
    int bIzq = 0;

    struct lectura{
      int sDer;
      int sIzq;
      int sCenter;  
    };

  public:
    operaciones() {
      pinMode(sLnDer,INPUT);
      pinMode(sLnIzq,INPUT);
      pinMode(sLnCenter,INPUT);
    
      pinMode(derA, OUTPUT);
      pinMode(derB, OUTPUT);
      pinMode(izqA, OUTPUT);
      pinMode(izqB, OUTPUT);

      pinMode(btnEncender,INPUT);
    
      pinMode(ledAtras,OUTPUT);

      pinMode(power, INPUT);
    }

    struct lectura leer(){
      struct lectura getLectura;
      getLectura.sDer = digitalRead(sLnDer);
      getLectura.sIzq = digitalRead(sLnIzq);
      getLectura.sCenter = digitalRead(sLnCenter);
      return getLectura; 
  }

    void avanzar(int v) {
      analogWrite(derB, v);  
      analogWrite(izqB, v);
    }

    void giros(int velDer, int velIzq) {
      analogWrite(derB, velDer);
      analogWrite(izqB, velIzq);
    }
    

    void casos() {
      struct lectura comp = leer();
      
      Serial.print("Derecho = ");
      Serial.println(comp.sDer);
      Serial.print("Center = ");
      Serial.println(comp.sCenter);
      Serial.print("Izq = ");
      Serial.println(comp.sIzq);
      
      if (comp.sIzq == 0  && comp.sCenter == 1 && comp.sDer == 0) {
        bDer = 0;
        bIzq = 0;
        digitalWrite(ledAtras,LOW);
        avanzar(vel);
        
      }else if(comp.sIzq == 0 && comp.sCenter == 0 && comp.sDer == 1 || bIzq == 1 ){
        
        digitalWrite(ledAtras,HIGH);
        giros(velVuelta,250);
        bDer = 0;
        bIzq = 1;
      }else if(comp.sIzq == 1 && comp.sCenter == 0 && comp.sDer == 0 || bDer == 1){
        digitalWrite(ledAtras,HIGH);
        giros(250,velVuelta);
        bDer = 1;
        bIzq = 0;
  }
    }
};

operaciones opc;
void setup() {
  Serial.begin(9600);
}


void loop() {
  opc.casos();
}
