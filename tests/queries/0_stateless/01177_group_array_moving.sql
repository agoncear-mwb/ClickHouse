SELECT groupArrayMovingSum(257)(-9223372036854775808), groupArrayMovingSum(1048575)(18446744073709551615), groupArrayMovingSum(9223372036854775807)(number * 9223372036854775807) FROM remote('127.0.0.{1..2}', numbers(3));
SELECT groupArrayMovingAvg(257)(-9223372036854775808), groupArrayMovingAvg(1048575)(18446744073709551615), groupArrayMovingAvg(9223372036854775807)(number * 9223372036854775807) FROM remote('127.0.0.{1..2}', numbers(3));
