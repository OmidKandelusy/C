# building stage
FROM gcc:13 AS builder

WORKDIR /app

COPY . .

RUN make
RUN mkdir -p build

# running stage
FROM debian:bookworm-slim

WORKDIR /app
COPY --from=builder /app/build ./build

CMD ["bash"]