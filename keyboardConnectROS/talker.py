#!/usr/bin/env python
import rospy
from std_msgs.msg import String
from std_msgs.msg import UInt16
key_in=""
def talker():
    pub = rospy.Publisher('PC2Arduino', UInt16, queue_size=10)
    rospy.init_node('talker', anonymous=True)
    rate = rospy.Rate(10) # 10hz
    pub2 = rospy.Publisher('PC2Arduino2', String, queue_size=10)
    rospy.init_node('talker', anonymous=True)
    rate = rospy.Rate(10) # 10hz
    key_in=""
    mode=1
    while mode != 88:
#        print("Leave input:88")
        mode = int(input("Leave input:88, Please Choice Mode:"))
#        print(mode)
        pub.publish(mode)
        rate.sleep()
	if mode == 0:
            print("Please use:  QWE  to control, Leave input:quit")
            print("             ASD")
            print("             ZXC")
	    while key_in != "quit":
                key_in = raw_input("control direction:")
#            	print("you input:")
#		print(key_in)
            	pub2.publish(key_in)
            	rate.sleep()

if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass
