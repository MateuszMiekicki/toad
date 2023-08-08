import socket
import json
import messages

host = 'localhost'
port = 5570
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.setsockopt(socket.SOL_SOCKET, socket.SO_SNDBUF, 1024*1024*10)
s.connect((host, port))


#get from user
mac_address = input("Enter MAC address: ")

s.sendall(mac_address.encode())

while True:
    data = s.recv(8192)
    if not data:
        continue
    try:
        data = json.loads(data.decode())
        print(data)
    except:
        print("Error while parsing JSON")
        alert = messages.make_alert_report(mac_address)
        s.sendall(alert.encode())
        continue
    if data.get('type') == 'request':
        response = None
        if data.get('purpose') == 'get_sensors_configuration':
            response = messages.make_get_sensors_configuration_response()
        elif data.get('purpose') == 'get_configuration':
            response = messages.make_get_configuration_response(mac_address)
        else:
            print("Unknown purpose")
            response = messages.make_response_failure("Unknown purpose")
        is_send_failure = input("Send failure? (y/n): ")
        if is_send_failure == 'y':
            response = messages.make_response_failure("user set failure")
        s.sendall(response.encode())
s.close()