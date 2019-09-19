from class_client import *
def main():
	client = Client("192.168.1.9")
	client.publish_topic("PT1000/Temperature", "23")

if __name__ == "__main__":
    main()
