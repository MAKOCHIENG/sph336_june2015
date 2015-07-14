/*
 * string.h
 *
 * Copyright (c) 2015 David Muriuki
 * see the LICENCE file
 */

#ifndef STRING_H_
#define STRING_H_

void strcatNum32Hex(uint8_t *dst, uint32_t dstSize, uint32_t num);
void Num16sToStr(uint8_t *dst, uint32_t dstSize, int16_t val);
void Num8sToStr(uint8_t *dst, uint32_t dstSize, signed char val);
void strcpy(uint8_t *dst, uint32_t dstSize, const unsigned char *src);
void strcat(uint8_t *dst, uint32_t dstSize, const unsigned char *src);

void strcatNum32Hex(uint8_t *dst, uint32_t dstSize, uint32_t num){
  unsigned char buf[sizeof("FFFFFFFF")]; /* maximum buffer size we need */
  unsigned char hex;
  int8_t i;

  buf[8] = '\0';
  i = 7;
  do {
    hex = (char)(num & 0x0F);
    buf[i] = (char)(hex + ((hex <= 9) ? '0' : ('A'-10)));
    num >>= 4;                          /* next nibble */
    i--;
  } while (i>=0);
  strcat(dst, dstSize, buf);
}

void Num16sToStr(uint8_t *dst, uint32_t dstSize, int16_t val){
  unsigned char *ptr =  ((unsigned char *)dst);
  unsigned char i=0, j;
  unsigned char tmp;
  unsigned char sign = (unsigned char)(val < 0);

  if (val==(int16_t)(0x8000)) { /* special case 0x8000/-32768: prevent overflow below. */
    strcpy(dst, dstSize, (unsigned char*)"-32768");
    return;
  }
  dstSize--; /* for zero uint8_t */
  if (sign) {
    val = -val;
  }
  if (val == 0 && dstSize > 0){
    ptr[i++] = '0';
    dstSize--;
  }
  while (val > 0 && dstSize > 0) {
    ptr[i++] = (unsigned char)((val % 10) + '0');
    dstSize--;
    val /= 10;
  }
  if (sign && dstSize > 0){
    ptr[i++] = '-';
    dstSize--;
  }
  for(j=0; j<(i/2); j++) { /* swap buffer */
    tmp = ptr[j];
    ptr[j] = ptr[(i-j)-1];
    ptr[(i-j)-1] = tmp;
  }
  ptr[i] = '\0';
}


void Num8sToStr(uint8_t *dst, uint32_t dstSize, signed char val){
  Num16sToStr(dst, dstSize, (int16_t)val);
}

void strcat(uint8_t *dst, uint32_t dstSize, const unsigned char *src){
  dstSize--; // for zero uint8_t
  // point to the end of the source
  while (dstSize > 0 && *dst != '\0') {
    dst++;
    dstSize--;
  }
  // copy the src in the destination
  while (dstSize > 0 && *src != '\0') {
    *dst++ = *src++;
    dstSize--;
  }
  // terminate the string
  *dst = '\0';
}

void strcpy(uint8_t *dst, uint32_t dstSize, const unsigned char *src){
  dstSize--; // for zero uint8_t
  while (dstSize > 0 && *src != '\0') {
    *dst++ = *src++;
    dstSize--;
  }
  *dst = '\0';
}

#endif /* STRING_H_ */
