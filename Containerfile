FROM alpine
RUN apk add vim
FROM alpine:latest
RUN apk add --no-cache gcc musl-dev
COPY heelo.c /heelo.c
RUN apt-get update && apt-get install -y gcc

