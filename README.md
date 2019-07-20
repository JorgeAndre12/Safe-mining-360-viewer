# Safe-mining-360-viewer
Currently and historically, in the mining industry we encounter a high level of injuries and accidents for distractions during mining activities. In the worst situation people who perform this activities lose their lives.

One example is the sinister that occured in the Czech Republic in December 21, 2018. An explosion killed 13 workers. Or the one in a mine in China with a roof collapse that killed 19 workers.

Recurring accidents like Methane and coal dust Blasting accidents kill 12,000 people a year.
According to the International Labour Organisation (ILO), while mining employs around 1% of the global labour force, it generates 8% of fatal accidents.

China has the world's largest mining industry, producing up to three billion tonnes of coal each year and already is introducing new safety laws to enhance miners security.

This kind of news are terrorific and tragedies like this can be avoided, the two key factors are effective communication and good information visibility.

https://www.nytimes.com/2018/12/21/world/europe/czech-republic-mine-explosion.html
https://www.theguardian.com/world/2019/jan/13/china-mine-accident-19-dead-and-two-trapped-after-roof-collapse

<img src="https://i.ibb.co/gdWNmzb/mining360.png" width="600">

Always use technology to improve the world, if you are a black hat or gray hat hacker please abstain at this point ......... or at least leave your star to make me feel less guilty XP.

# Table of contents

* [Introduction](#introduction)
* [Materials](#materials)
* [Connection Diagram](#connection-diagram)
* [Theta and Streaming Setup](#theta-and-streaming-setup)
* [MQTT Setup](#mqtt-setup)
* [ESP32 Setup](#esp32-setup)
* [The Final Product](#the-final-product)
* [Future Rollout](#future-rollout)
* [Our Plugin](#our-plugin)
* [References](#references)

## Introduction:

We are going to build a complete monitoring system that allow the miners to have a 360° visibility. The main point of all this is that the miner would NOT have to be present in the area as everything will be done remotely via robotic arm.

Our development will connect the RICOH THETA 360° camera. This in order to remotely move a Robotic arm via VR that will serve as a PoC for later developments.

Current Solutions:

- Epiroc offers machinery that can be operated remotely using directional camera to minimize risk and accidents when dig caves to set explosives.

- Komatsu bring large arms placed in truck to dig holes using a mechanical way with a safety range area to operate.

- Minemaster bring an auxiliary digger that bring the operator physical view and wide range to manually operate the dig arm.

These suppliers are recognized in the market but much of them use manual technology and require people in the place to perform their activities.

## Materials:

Hardware:
- Ricoh Theta V                                    x1.
https://theta360.com/es/about/theta/v.html
- Robotic Arm                                      x1.
https://www.amazon.com/OWI-Robotic-Soldering-Required-Extensive/dp/B0017OFRCY
- ESP32                                            x2.
https://www.adafruit.com/product/3405
- Dupont Wire                                      x30.
- 8 Channel DC 5V Relay Module with Optocoupler    x1.
https://www.amazon.com/Elegoo-Module-Optocoupler-Arduino-Raspberry/dp/B07F623PHG

Software:
- Android Studio.
- Anrduino IDE.
- Theta Software:
https://support.theta360.com/en/download/
- Ricoh Theta native API.
- Cloud MQTT.

## Connection Diagram:

This is the connection diagram of the system:

<img src="https://i.ibb.co/QJj60Mq/Diagram.png" width="600">

This the ARM Relay Diagram:

<img src="https://i.ibb.co/H24DQ8N/ARM-bb.png" width="600">

This is the ARM Control Diagram:

<img src="https://i.ibb.co/n1G0b6j/ARMcontrol-bb.png" width="600">

## Theta and Streaming Setup:

<img src="https://media.wired.com/photos/5a679b59d0d73e186fbefd64/master/w_799,c_limit/Ricoh-TopArt.jpg" width="600">

Connect the Camera to the PC and put it in Live node.

- Press the mode button until the word Live appears, this mode is only accessible when the camera is connected to a computer.

### You must configure the camera to perform a live streaming:

- Install the following softwares on your computer:
https://topics.theta360.com/uk/faq/c_06_v/304_1/
https://obsproject.com/

### Connect the camera to the PC and configure the OBS to check that we have an image:

- Open OBS and add Source.

<img src="https://i.ibb.co/tMycnSy/ThetaOBS.png" width="600">

- Add Video Capture Device.

<img src="https://i.ibb.co/HBTDgMt/theta1.png" width="600">

- Add the device name (any name).

<img src="https://i.ibb.co/vBbyZsr/theta2.png" width="600">

- Add the device name (any name).

<img src="https://i.ibb.co/vBbyZsr/theta2.png" width="600">

- Select "Ricoh Theta V FullHD or 4k".

<img src="https://i.ibb.co/ZTrcBMM/theta3.png" width="600">

- If everything works fine, we should see the image of the camera in the OBS.

<img src="https://i.ibb.co/b62cLS0/theta4.png" width="600">

### Configure the Streaming on Youtube:

- Go to the YouTube page and go to the "go live" tab.

<img src="https://i.ibb.co/YfxMLJV/theta5.png" width="600">

- Create your new Streaming, i recommend unlisted so that your streaming is not made public.

<img src="https://i.ibb.co/2kvTyVS/ricoh6.png" width="600">

- Once the streaming is created enter in "settings".

<img src="https://i.ibb.co/6YmLmn6/theta6.png" width="600">

- Activate the transmission in 360.

<img src="https://i.ibb.co/qgn4hLK/theta7.png" width="600">

- Enter in OBS Settings.

<img src="https://i.ibb.co/Q8KnFqF/Theta8.png" width="600">

- In the "stream" tab, set the values exactly as the image and paste your key in OBS.

<img src="https://i.ibb.co/6XNzFY8/theta9.png" width="600">

- Start the transmition.

<img src="https://i.ibb.co/DkRr4sJ/theta.png" width="600">

- If everything goes well you should see a preview of what the camera sees.

<img src="https://i.ibb.co/ZcTF2wQ/theta10.png" width="600">

- Since you have the link, you can open it in any VR viewer.

<img src="https://i.ibb.co/2vM8Mw4/theta11.png" width="600">

## MQTT Setup:

<img src="https://www.cloudmqtt.com/images/iot.png" width="600">

In the case of MQTT you can use any kind of MQTT available in the market, IBM, AWS, Google IoT, CloudMQTT, etc...

- We will use CloudMQTT for ease of use, create a free account and continue with the tutorial.
Link: https://www.cloudmqtt.com/

- We need the MQTT Cloud credentials for the MQTT configuration in the next step.

<img src="https://i.ibb.co/K7zMqs8/cloud-mqtt.png" width="600">

## ESP32 Setup:

<img src="https://cdn-shop.adafruit.com/1200x900/3405-06.jpg" width="600">

Download the files in the "Arduino Files" folder and we will have to configure two modules of ESP32, one of the arm and one for the control, in both we will have to configure the WiFi and CloudMQTT credentials.

      const char* ssid = "YOUR_SSID";
      const char* password =  "PASSWORD";
      const char* mqttServer = "m12.cloudmqtt.com";
      const int mqttPort = YOURPORT;
      const char* mqttUser = "YOURUSER";
      const char* mqttPassword = "YOURPASSWORD";
      bool sw = false;

For each ESP32, change the name with which it will connect to CloudMQTT.

First ESP32:

      if (client.connect("ESP32Client1", mqttUser, mqttPassword )) {

      Serial.println("connected");  

      }

Second ESP32:

      if (client.connect("ESP32Client2", mqttUser, mqttPassword )) {

      Serial.println("connected");  

      }

After that, the modules should work without problems.

## The Final Product:

Robot Arm Driver, Final Assembly:
<img src="https://i.ibb.co/M7YVDTf/20190718-234535.jpg" width="800">

Robot Arm Driver, Internal:
<img src="https://i.ibb.co/pZhMdVD/20190718-234800.jpg" width="800">

Robot Arm Control, Final Assembly:
<img src="https://i.ibb.co/PYdg5yH/20190718-234910.jpg" width="800">

Robot Arm Control, Internal:
<img src="https://i.ibb.co/cF953g0/20190718-234308.jpg" width="800">

## Important Note:

During the development process, I tried to develop the video streaming and image processing through Android Studio in a plugin, however the algorithms did not work and unfortunately it was decided to make an extra plugin for the contest in addition to the project.

It was decided to make an independent plugin for the ricoh theta plugin store: https://pluginstore.theta360.com/

### Our Epic Video:

Video: Click on the image
[![Video](https://i.ibb.co/gdWNmzb/mining360.png)](https://youtu.be/JZ9efUy9qbo)

Sorry github does not allow embed videos.

## Future Rollout:

// Inventate algo XP

## Our Plugin:

### Download Link: Insertar link cuando este en la tienda.

<img src="http://theta360.guide/plugin-user-guide/main/img/install/store.png" width="400">

### Install:

Original Install Guide Link: http://theta360.guide/plugin-user-guide/main/install/

Connect your THETA to your computer and click on the Install button.

<img src="http://theta360.guide/plugin-user-guide/main/img/install/install.png" width="400">

The Ricoh Desktop Application will automatically start for plug-in installation.

### Configure Plug-in to Launch:

As the THETA V can save multiple plug-ins to internal storage, you need to specify the active plug-in to launch when the camera is put into plug-in mode.

There are many ways to select the active plug-in.

Developers can use the open API of the THETA to set the plug-in. This document focuses on using the official desktop app to specify the active plug-in.

### Set Active Plug-in with Desktop App:

Connect your desktop computer or laptop to the THETA with a USB cable. Under the file menu, select Plug-in management....

<img src="http://theta360.guide/plugin-user-guide/main/img/install/plug-in-manager.png" width="400">

Select the plug-in that you want to use.

<img src="http://theta360.guide/plugin-user-guide/main/img/install/plug-in-list.png" width="400">

### Idea:

Develop a plugin that could use OpenCv to process images and generate interesting filters for the camera.

Filters to be used:

- Image Equalization (color).
- Binarization of image or Threshold (Red, Green and Blue).
- Grayscale.
- Blur.
- Erosion-Dilatation.
- Negative

### How it Works:

Once activated the Plugin, we can select the desired filter using the "Mode" button, depending on the color that the Wi-Fi symbol has, it will be the effect that will be applied to the image.

- Blue: Image Equalization (color).
- Green: Image Binarization or Threshold (Red, Green and Blue).
- Cyan: Grayscale.
- Magenta: Blur.
- Yellow: Erosion-Dilatation.
- White: Negative.
- Once the filter is selected, we only have to press the Shutter button to take the image and save it, the image will be saved in a folder called "Filtered Images".

Note: when the filter is being applied the WiFi symbol will flash, until it stops blinking, do not press any other button, this process takes 1 - 4 seconds depending on the filter.

### Developing:

The filters were made with the following code lines:

- Image Equalization (color):

      fileUrl = String.format("%s/%s_equalize.jpg", Constants.PLUGIN_DIRECTORY, dateTimeStr);
      Mat rgbImage = new Mat(img.size(), img.type());
      Imgproc.cvtColor(img, img, Imgproc.COLOR_RGB2YCrCb);
      List<Mat> channels = new ArrayList<Mat>();
      Core.split(img, channels);
      Imgproc.equalizeHist(channels.get(0), channels.get(0));
      Core.merge(channels, img);
      Imgproc.cvtColor(img, img, Imgproc.COLOR_YCrCb2BGR);

- Binarization of image or Threshold (Red, Green and Blue):

      fileUrl = String.format("%s/%s_threshold.jpg", Constants.PLUGIN_DIRECTORY, dateTimeStr);
      Mat rgbImage = new Mat(img.size(), img.type());
      Imgproc.cvtColor(img, img, Imgproc.COLOR_RGB2YCrCb);
      Imgproc.threshold(img, img, 127.0, 255.0, Imgproc.THRESH_BINARY);
      Imgproc.cvtColor(img, img, Imgproc.COLOR_YCrCb2RGB);

- Grayscale:

      fileUrl = String.format("%s/%s_gray.jpg", Constants.PLUGIN_DIRECTORY, dateTimeStr);
      Imgproc.cvtColor(img, img, Imgproc.COLOR_RGB2GRAY);

- Blur:

      fileUrl = String.format("%s/%s_blur.jpg", Constants.PLUGIN_DIRECTORY, dateTimeStr);
      Imgproc.cvtColor(img, img, Imgproc.COLOR_RGB2BGR);
      Imgproc.blur(img, img, new Size(25,25));

- Erosion-Dilatation.

      fileUrl = String.format("%s/%s_erodedilate.jpg", Constants.PLUGIN_DIRECTORY, dateTimeStr);
      Imgproc.cvtColor(img, img, Imgproc.COLOR_RGB2GRAY);
      Imgproc.threshold(img, img, 0, 255, Imgproc.THRESH_BINARY_INV+Imgproc.THRESH_OTSU);

- Negative:

      fileUrl = String.format("%s/%s_negative.jpg", Constants.PLUGIN_DIRECTORY, dateTimeStr);
      Core.bitwise_not(img,img);

### Video:

Video: Click on the image
[![Demo](https://i.ibb.co/WWJxD4y/Sin-t-tulo-1.png)](https://youtu.be/GXGoOoDZA8g)

Sorry github does not allow embed videos.
