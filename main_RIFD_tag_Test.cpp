//Test of cheap 13.56 Mhz RFID-RC522 module from eBay
//This code is based on Martin Olejar's and Thomas Kirchner's MFRC522 libraries. Minimal changes
//Adapted for FRDM-K64F from Freescale, in 07/21/2014 by Clovis Fritzen.

#include "mbed.h"
#include "MFRC522.h"

// FRDM-K64F (Freescale) Pin for MFRC522 reset
#define MF_RESET    PTD0

DigitalOut LedGreen(LED2);

//Serial connection to PC for output
Serial pc(PTC17, PTC16); // serial comm on the FRDM board

//MFRC522    RfChip   (SPI_MOSI, SPI_MISO, SPI_SCK, SPI_CS, MF_RESET);
MFRC522    RfChip   (PTD2, PTD3, PTD1, PTE25, PTD0);

int main(void) {
  printf("starting...\n");

  // Init. RC522 Chip
  RfChip.PCD_Init();

  while (true) {
    LedGreen = 1;

    // Look for new cards
    if ( ! RfChip.PICC_IsNewCardPresent())
    {
      wait_ms(100);
      continue;
    }

    // Select one of the cards
    if ( ! RfChip.PICC_ReadCardSerial())
    {
      wait_ms(100);
      continue;
    }

    LedGreen = 0;

    // Print Card UID
    printf("Card UID: ");
    for (uint8_t i = 0; i < RfChip.uid.size; i++)
    {
      printf(" %X02", RfChip.uid.uidByte[i]);
    }
    printf("\n\r");

    // Print Card type
    uint8_t piccType = RfChip.PICC_GetType(RfChip.uid.sak);
    printf("PICC Type: %s \n\r", RfChip.PICC_GetTypeName(piccType));
    wait_ms(100);
  }
}