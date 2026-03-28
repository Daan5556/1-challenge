while true; do
  mosquitto_pub -h localhost -t 'sensors' -m 'vehicle_camera,edge_device_id=ED-1001-01 value=64,count=4'

  sleep 5
done
