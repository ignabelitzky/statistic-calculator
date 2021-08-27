# Statistics Calculator
Statistics calculator. It performs the following operations:
* Arithmetic Mean
* Median
* Minimum
* Maximum
* Variance
* Standard Deviation (n-1)
* Lower Quartile (in development)
* Upper Quartile (in development)

## Getting Started
To compile the Static Calculator you should open the CMakeList.txt file with QT Creator and now you can build the app and run on your Linux machine.

### Input/Output of the data/calculations
* The data can be entered manually or via a space-separated numbers file.
* The calculations are very easy to show, just select what you want to see and press "Display selected data".
* The data can be showed just clicking on the "Show Graphic" button. You must select the drawGraph.py script to display the graphic of the data.

### Screenshot and videoclip
![Screenshot](https://github.com/ignabelitzky/statistics-calculator/blob/main/statistics-calculator/images/screenshots/screenshot_img3.png)

Here is a [clip of the program](https://youtu.be/4WeZVzO6_UQ)

### Contributing
This piece of software is far for complete so pull requests are welcome.

### License
[GNU General Public License v3.0](https://www.gnu.org/licenses/gpl-3.0.html)

### TO-DO
- The posibility of see all the data and do modifications.
- Improve the drawGraph.py script for showing the graphical representation of the data.
- Implement lower and upper quartile.
- Improve GUI with a background and some colours (remainder: make the interface more modern).

### Known issues
- It is not a modular code.
- The load of data it's not perfect (i.e it does not check if you type letters or if the format of the input file is correct).
