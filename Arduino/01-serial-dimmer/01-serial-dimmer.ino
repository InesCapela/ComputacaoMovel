
const int _ledpin = 13;

void setup(){
  Serial.begin(9600);
  pinMode(_ledpin, OUTPUT);
  Serial.println("Por favor introduza um valor entre 0 e 255:");
}

void loop(){

  if(Serial.available() > 0) {

    // Ler input e converter
    String value = Serial.readString();
    int n = value.toInt();

    // Apply
    if(n >= 0 && n <=255){
      Serial.print("> Aplicando o valor: ");
      Serial.println(n);
      analogWrite(_ledpin, n);

    // Invalid number
    } else {
      Serial.println("[!] Valor inválido! Introduza um valor entre 0 e 255:");
    }

  }
}


