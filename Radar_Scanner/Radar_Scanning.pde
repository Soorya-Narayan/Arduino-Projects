import processing.serial.*; // Import library for serial communication
import java.awt.event.KeyEvent; // Import library for reading data from the serial port
import java.io.IOException;
Serial serialPort; // Define Serial object
// Define variables
String angleData = "";
String distanceData = "";
String rawData = "";
String objectStatus;
float pixelDistance;
int angleInDegrees, distanceInCm;
int delimiterIndex1 = 0;
int delimiterIndex2 = 0;
PFont customFont;

void setup() {
  size(1200, 700); // Set the screen resolution
  smooth();
  serialPort = new Serial(this, "COM7", 9600); // Start serial communication
  serialPort.bufferUntil('.'); // Read data from the serial port up to the character '.'
}

void draw() {
  fill(50, 168, 82); // Set background color
  noStroke();
  fill(0, 5); 
  rect(0, 0, width, height - height * 0.065); 
  
  fill(50, 168, 82); // Set radar color
  drawRadar(); 
  drawRadarLine();
  drawDetectedObject();
  displayText();
}

void serialEvent(Serial serialPort) { // Start reading data from the Serial Port
  rawData = serialPort.readStringUntil('.');
  rawData = rawData.substring(0, rawData.length() - 1);
  
  delimiterIndex1 = rawData.indexOf(","); // Find the character ',' and store its position
  angleData = rawData.substring(0, delimiterIndex1); // Extract angle data
  distanceData = rawData.substring(delimiterIndex1 + 1, rawData.length()); // Extract distance data
  
  // Convert string variables to integers
  angleInDegrees = int(angleData);
  distanceInCm = int(distanceData);
}

void drawRadar() {
  pushMatrix();
  translate(width / 2, height - height * 0.074); // Move starting coordinates
  noFill();
  strokeWeight(2);
  stroke(50, 168, 82);
  
  // Draw radar arcs
  arc(0, 0, (width - width * 0.0625), (width - width * 0.0625), PI, TWO_PI);
  arc(0, 0, (width - width * 0.27), (width - width * 0.27), PI, TWO_PI);
  arc(0, 0, (width - width * 0.479), (width - width * 0.479), PI, TWO_PI);
  arc(0, 0, (width - width * 0.687), (width - width * 0.687), PI, TWO_PI);
  
  // Draw angle lines
  line(-width / 2, 0, width / 2, 0);
  line(0, 0, (-width / 2) * cos(radians(30)), (-width / 2) * sin(radians(30)));
  line(0, 0, (-width / 2) * cos(radians(60)), (-width / 2) * sin(radians(60)));
  line(0, 0, (-width / 2) * cos(radians(90)), (-width / 2) * sin(radians(90)));
  line(0, 0, (-width / 2) * cos(radians(120)), (-width / 2) * sin(radians(120)));
  line(0, 0, (-width / 2) * cos(radians(150)), (-width / 2) * sin(radians(150)));
  line((-width / 2) * cos(radians(30)), 0, width / 2, 0);
  popMatrix();
}

void drawDetectedObject() {
  pushMatrix();
  translate(width / 2, height - height * 0.074); // Move starting coordinates
  strokeWeight(9);
  stroke(255, 0, 0); // Set object color
  pixelDistance = distanceInCm * ((height - height * 0.1666) * 0.025); // Convert distance from cm to pixels
  
  // Limit the range to 40 cm
  if (distanceInCm < 40) {
    // Draw object according to angle and distance
    line(pixelDistance * cos(radians(angleInDegrees)), -pixelDistance * sin(radians(angleInDegrees)), 
         (width - width * 0.505) * cos(radians(angleInDegrees)), -(width - width * 0.505) * sin(radians(angleInDegrees)));
  }
  popMatrix();
}

void drawRadarLine() {
  pushMatrix();
  strokeWeight(9);
  stroke(0, 255, 0); // Set radar line color
  translate(width / 2, height - height * 0.074); // Move starting coordinates
  line(0, 0, (height - height * 0.12) * cos(radians(angleInDegrees)), -(height - height * 0.12) * sin(radians(angleInDegrees))); // Draw line according to angle
  popMatrix();
}

void displayText() { // Draw texts on the screen
  pushMatrix();
  if (distanceInCm > 40) {
    objectStatus = "Out of Range";
  } else {
    objectStatus = "In Range";
  }
  fill(0, 0, 0);
  noStroke();
  rect(0, height - height * 0.0648, width, height);
  fill(50, 168, 82);
  textSize(25);
  
  text("10 cm", width - width * 0.3854, height - height * 0.0833);
  text("20 cm", width - width * 0.281, height - height * 0.0833);
  text("30 cm", width - width * 0.177, height - height * 0.0833);
  text("40 cm", width - width * 0.0729, height - height * 0.0833);
  textSize(40);
  text("Radar System", width - width * 0.875, height - height * 0.0277);
  text("Angle: " + angleInDegrees + " °", width - width * 0.48, height - height * 0.0277);
  text("Dist.: ", width - width * 0.26, height - height * 0.0277);
  if (distanceInCm < 40) {
    text("        " + distanceInCm + " cm", width - width * 0.225, height - height * 0.0277);
  }
  textSize(25);
  fill(50, 168, 100);
  translate((width - width * 0.4994) + width / 2 * cos(radians(30)), 
            (height - height * 0.0907) - width / 2 * sin(radians(30)));
  rotate(-radians(-60));
  text("30°", 0, 0);
  resetMatrix();
  translate((width - width * 0.503) + width / 2 * cos(radians(60)), 
            (height - height * 0.0888) - width / 2 * sin(radians(60)));
  rotate(-radians(-30));
  text("60°", 0, 0);
  resetMatrix();
  translate((width - width * 0.507) + width / 2 * cos(radians(90)), 
            (height - height * 0.0833) - width / 2 * sin(radians(90)));
  rotate(radians(0));
  text("90°", 0, 0);
  resetMatrix();
  translate(width - width * 0.513 + width / 2 * cos(radians(120)), 
            (height - height * 0.07129) - width / 2 * sin(radians(120)));
  rotate(radians(-30));
  text("120°", 0, 0);
  resetMatrix();
  translate((width - width * 0.5104) + width / 2 * cos(radians(150)), 
            (height - height * 0.0574) - width / 2 * sin(radians(150)));
  rotate(radians(-60));
  text("150°", 0, 0);
  popMatrix(); 
}
