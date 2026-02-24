FROM gcc:latest
WORKDIR /app
COPY app.cpp .
RUN g++ app.cpp -o app
EXPOSE 8080
CMD ["./app"]
