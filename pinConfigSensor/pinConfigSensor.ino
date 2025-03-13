int delayFuncMS(long setTime){
  volatile int i = 0;
  volatile long time = setTime*16;
  for(i; i<=time;i++){

  }
  i=0;
}

int main(){
  USART_Init();
  DDRB = DDRB | 0x06;
  long microSeconds = 0;
  long duration;
  int distance = 0;
  while(1){
    PINB &= ~(0x02);
    delayFuncMS(2);
    PINB |= 0x02;
    delayFuncMS(10);
    PINB &= ~(0x02);
    
    microSeconds = 0;
    do{
      microSeconds+=16;
    }while((PINB & 0x04) == 0);
    duration = microSeconds;
    distance = duration * 0.0343/2;
    Serial.println(distance); 


    delayFuncMS(1000);
  }
  return 1;
}

// Function to initialize USART for serial communication
void USART_Init() {
  unsigned int ubrr = F_CPU / 16 / 9600 - 1;  // Baud rate = 9600
  // Set baud rate
  UBRR0H = (unsigned char)(ubrr >> 8);
  UBRR0L = (unsigned char)ubrr;
  
  // Enable transmitter
  UCSR0B = (1 << TXEN0);
  
  // Set frame format: 8 data bits, 1 stop bit
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

// Function to send data over USART (for serial printing)
void USART_Transmit(unsigned char data) {
  while (!(UCSR0A & (1 << UDRE0))) {
    // Wait for empty transmit buffer
  }
  UDR0 = data;  // Put data into the buffer, sends the data
}

// Function to send a string over USART
void Serial_Print(const char* str) {
  while (*str) {
    USART_Transmit(*str++);
  }
}

// Function to print integers (distance in this case)
void Serial_Println(int num) {
  char buffer[16];
  itoa(num, buffer, 10); // Convert the integer to a string
  Serial_Print(buffer);  // Print the string
  USART_Transmit('\n');  // Print newline character
}