### Stream Task

## Requirements

* OpenCV 4.x.x
* Pthread

## Build and Run
```
make -j(max_core_number-1)
./main
```

## Config
```
Could be changed in "config.json" file buffer size, random starting and ending mseconds etc.
```

NOTE :  I used Lab color channel for calculating intensity. Lab channel gives more information about images. For that reason I used it.
