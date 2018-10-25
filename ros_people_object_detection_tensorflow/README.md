# ROS People Object Detection & Action Recognition Tensorflow

[![Open Source Love](https://badges.frapsoft.com/os/v2/open-source-200x33.png?v=103)](https://github.com/cagbal/ros_people_object_detection_tensorflow) [![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](https://github.com/cagbal/ros_people_object_detection_tensorflow)

An extensive ROS toolbox for object detection & tracking and face recognition with 2D and 3D support which makes your Robot understand the environment. Now it has action recognition capability by using i3d module in tensorflow hub.

# Demo

### Object Detector Output:
![Object Detection](https://github.com/cagbal/ros_people_object_detection_tensorflow/blob/master/images/objects.gif?raw=true)
### ----------
### Face Recognizer Output:
![Face Recognition](https://github.com/cagbal/ros_people_object_detection_tensorflow/blob/master/images/people.gif?raw=true)
### ----------
### Mask RCNN Output:
![Mask RCNN](https://github.com/cagbal/ros_people_object_detection_tensorflow/blob/master/images/mask_rcnn_masked.png?raw=true&s=1)
### ----------
### Object Tracker Output:
![Tracking](https://github.com/cagbal/ros_people_object_detection_tensorflow/blob/master/images/tracking.png?raw=true&s=1)


NOTE: The object detection codes are based on jupyter notebook inside of the object detection API. The code also recognizes the faces that in the scene by using amazing [face_recognition](https://github.com/ageitgey/face_recognition) library. Also, The code can now track the detections by using Sort tracker(Kalman based) thanks to [this repo](https://github.com/ZidanMusk/experimenting-with-sort). For licences, please check the licences of these repos as well.

# Flowchart
![Flowchart](https://github.com/cagbal/ros_people_object_detection_tensorflow/blob/master/images/people_object_detection_diagram.png?raw=true)

# Features

  - Detects the objects in images coming from a camera topic  
  - Publishes the scores, bounding boxes and labes of detection
  - Recognizes the actions and published the probabilities and labels returned by I3D model provided in tensorflow_hub
  - Publishes detection image with bounding boxes as a sensor_msgs/Image
  - Publishes the face recognition results
  - Publishes the tracking number(an integer) for each tracked object assigned by object tracker
  - If the Depth stream avaliable from a kinect or from a similar device, it can publish the depth of the face
  - TODO: Depth estimation is based on median filter applied to non-nan values inside the face bounding box, if you have any suggestions: [![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](https://github.com/cagbal/ros_people_object_detection_tensorflow)
  - Parameters can be set fom a Yaml file
  - Detects the faces inside the person area
  - [Completed] ~~TODO: you can currently use MASK RCNN, but it just publishes the mask drawn on the image, I am trying to publish the mask as a ROS message.~~ Now, it publishes it under detections.detection.mask.mask as an sensor image.
  - [Completed thanks to @thjoshi] ~~TODO: I am not happy with tracking.~~
  - TODO: I need to test the action recognition  module thoroughly. [![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](https://github.com/cagbal/ros_people_object_detection_tensorflow)

### Tech

This repo uses a number of open source projects to work properly:

* [Tensorflow]
* [Tensorflow-Object Detection API]
* [Tensorflow Hub]
* [ROS]
* [Numpy]
* [face_recognition] https://github.com/ageitgey/face_recognition
* [dlib]
* [cob_perception_common] https://github.com/ipa-rmb/cob_perception_common.git
* [protobuf]

For Tracker part:
* scikit-learn
* scikit-image
* FilterPy

### Installation

First, tensorflow should be installed on your system.

Then,
```sh
$ cd && mkdir -p catkin_ws/src && cd ..
$ catkin_make && cd src
$ git clone --recursive https://github.com/cagbal/
ple_object_detection_tensorflow.git
$ git clone https://github.com/cagbal/cob_perception_common.git
$ cd cob_people_object_detection_tensorflow/src
$ protoc object_detection/protos/*.proto --python_out=.
$ cd ~/catkin_ws
$ rosdep install --from-path src/ -y -i
$ catkin_make
$ pip install face_recognition
```

The repo includes the fastest mobilenet based method, so you can skip the steps below.

Then, install a model from [Model Zoo](https://github.com/tensorflow/models/blob/master/research/object_detection/g3doc/detection_model_zoo.md)  of tensorflow object detection.

and put those models into src/object_detection/, lastly set the model_name parameter of [launch/cob_people_object_detection_tensoflow_params.yaml](https://github.com/cagbal/ros_people_object_detection_tensorflow/blob/master/launch/cob_people_object_detection_tensorflow_params.yaml)

### Running

Turn on your camera driver in ROS and set your input RGB topic name in yaml config file under launch directory. The default is for openni2.

For running everything, (This will work for both 2D and 3D)

```sh
$ roslaunch cob_people_object_detection_tensorflow alltogether.launch
```

The code above will start everything. It is perfect for starting with this repo. However, if you want some flexibility then you need to launch every node one by one. As below:

For object detection:

```sh
$ roslaunch cob_people_object_detection_tensorflow cob_people_object_detection_tensorflow.launch
```

Then, it starts assigning an ID to the each detected objects and publishes the results to /object_tracker/tracks. Note that detected tracked object numbers may differ.

If you also want to run the tracker,

```sh
$ roslaunch cob_people_object_detection_tensorflow cob_people_object_tracker.launch
```

If you also want to run the face_recognition,

put face images inside people folder and launch:

```sh
$ roslaunch cob_people_object_detection_tensorflow cob_face_recognizer.launch
```

If you also want to run depth finder,

```sh
$ roslaunch cob_people_object_detection_tensorflow projection.launch
```

and it sets detections.pose.pose.position.x/y/z and pusblishes it.

If you also want to run action recognition,

```sh
$ roslaunch cob_people_object_detection_tensorflow action_recognition.launch
```

Then, you will see the probabilities published on /action_recognition/action_predictions

##### Subscibes to:
- To any RGB image topic that you set in *params.yaml file.

##### Publishes to:
- /object_detection/detections (cob_perception_msgs/DetectionArray) Includes all the detections with probabilities, labels and bounding boxes
- /object_detection/detections_image (sensor_msgs/Image) The image with bounding boxes
- /object_tracker/tracks (cob_perception_msgs/DetectionArray) Includes just the tracked objects and their bounding boxes, labels. Here, ID is the detection id assigned by tracker. Example: DetectionArray.detections[0].id
- /face_recognizer/faces (cob_perception_msgs/DetectionArray) Face labels with face and people bounding boxes
- /action_recognition/action_predictions (cob_perception_msgs/ActionRecognitionmsg) Action recognition probabilities with Kinetics 600 Dataset labels

### Performance
The five last detection times from my computer(Intel(R) Core(TM) i7-6820HK CPU @ 2.70GHz) in seconds:
- 0.105810880661
- 0.108750104904
- 0.112195014954
- 0.115020036697
- 0.108013153076

### Contributors
- cagbal
- thjoshi

License
----

Apache (but please also look at tensorflow, tf object detection, face_recognition and dlib licences)


Acknowledgement
---
My works in Fraunhofer IPA, Stuttgart are supported by SOCRATES which is an MSCA-ITN-2016 – Innovative Training Networks funded by EC under grant
agreement No 721619.

You can find a lot of information regarding SOCRATES [here](http://www.socrates-project.eu/).
