# Imagine de bază cu GCC instalat
FROM gcc:latest

# Directorul de lucru
WORKDIR /map

# Copiază fișierele sursă în container
COPY map/ /map

# Compilează fiecare fișier separat
RUN gcc -o map_hardcoded c_tari.c
RUN gcc -o map_input tari_input.c

# Mesaj implicit pentru rulare
CMD ["sh", "-c", "echo 'Pentru a rula: ./map_hardcoded sau ./map_input'"]
