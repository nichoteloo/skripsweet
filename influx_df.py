#!/home/nichotelo/influx-env/bin/python
# coding: utf-8

from influxdb import DataFrameClient
import pandas as pd

host = '127.0.0.1'
port = 8086
user = 'admin'
password = 'adminpassword'
dbname = 'sensors'

client = DataFrameClient(host=u'localhost', port=8086, username=u'admin', password=u'adminpassword')
client.switch_database(dbname)

q = 'select * from "esp32/rssi/json"'

result = client.query(q)
df = result['rssi1'].head()

print(df)