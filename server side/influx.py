from influxdb import DataFrameClient
from influxdb import InfluxDBClient
from influxdb.exceptions import InfluxDBClientError
from influxdb.exceptions import InfluxDBServerError

# Optimize this query to your needs – potentially a HUGE query
__query__ = 'SELECT * FROM "esp32/rssi/json" LIMIT 10'

def main():
    print('Playing with InfluxDB-Python:\n'
          + '\tquery_print(): {}\n'.format(query_print.__doc__)
          + '\tdf_print(): {}\n'.format(df_print.__doc__))
    query_print()
    df_print()


def query_print():
    """Form and submit a query, print JSON output"""
    try:
        client = InfluxDBClient(host='127.0.0.1',
                                port=8086,
                                username='admin',
                                password='adminpassword',
                                database='sensors')
        query = client.query(__query__)
    except InfluxDBClientError as ice:
        print('InfluxDB client error:\n{}'.format(ice))
        exit(1)
    except InfluxDBServerError as ise:
        print('InfluxDB server error:\n{}'.format(ise))
        exit(1)
    except ConnectionRefusedError as cre:
        print('Connection refused. Is database accessible?\n{}'.format(cre))
        exit(1)
    except Exception as e:
        print('An error occurred, '
              + 'check your database credentials.\n{}'.format(e))
        exit(1)

    # query.raw prints JSON instead of a ResultSet
    print(query.raw)


def df_print():
    """Form and submit a query, print pretty pandas DataFrame output"""
    try:
        client = DataFrameClient(host='127.0.0.1',
                                 port=8086,
                                 username='admin',
                                 password='adminpassword',
                                 database='sensors')
        query = client.query(__query__)
    except InfluxDBClientError as ice:
        print('InfluxDB client error: {}\n'.format(ice))
        exit(1)
    except InfluxDBServerError as ise:
        print('InfluxDB server error: {}\n'.format(ise))
        exit(1)
    except ConnectionRefusedError as cre:
        print('Connection refused. Is database accessible?\n{}'.format(cre))
        exit(1)
    except Exception as e:
        print('An error occurred, '
              + 'check your database credentials.\n{}'.format(e))
        exit(1)

    print(query)


if __name__ == '__main__':
    main()