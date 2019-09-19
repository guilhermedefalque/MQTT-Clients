import paho.mqtt.client as mqtt

class Client(object):
	def __init__(self, broker_address):
		self.client = mqtt.Client("P1")
		self.client.connect(broker_address)
	def publish_topic(self, topic, text):
		self.client.publish(topic, text)
