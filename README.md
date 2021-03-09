# Trinity CLI

A simple C program to run the simulations from the [Trinity study](https://en.wikipedia.org/wiki/Trinity_study) from your command line. 

### Usage

To run the simulation from the Trinity study using an initial capital of $1M, a $40K withdrawal rate, 0.15% yearly fees and a required duration of 30 years, run the following command:


```sh
trinity -c 1000000 -w 40000 -f 0.15 -d 30
```

Output:
```sh
Capital: 1000000.00
Withdrawal: 40000.00 per month
Fees: 0.15% per year
Duration: 30 years
Success ratio: 1404 / 1441 (97.43%)
```

Data is coming from from [Robert Shiller's website](http://www.econ.yale.edu/~shiller/data.htm) and consists of S&P 500 stock returns & inflation data dating back to 1871. It is embedded in the binary, so the program runs regardless of its location on your filesystem.


### Installing

Download one of the prebuilt binaries for your platform from the releases page or build from source using the instructions below.

```sh
git clone git@github.com:dannyvankooten/trinity.git
make
sudo make install
```


### License

MIT licensed.