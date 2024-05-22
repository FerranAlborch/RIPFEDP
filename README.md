# RFEDP
 Repository including randomized functional encryption for differential privacy

# How to build and run the docker image
### Build
```
docker build -t rfedp .
```

### Running the image
```
docker run -it rfedp
```

This command will give you access to the command line inside the image. You can run a test using the following command:
```
./RFEDP 10 16 24 7
```