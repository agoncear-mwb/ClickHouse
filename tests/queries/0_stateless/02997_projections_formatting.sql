CREATE TEMPORARY TABLE t_proj (t DateTime, id UInt64, PROJECTION p (SELECT id, t ORDER BY toStartOfDay(t))) ENGINE = MergeTree ORDER BY id;
SHOW CREATE TEMPORARY TABLE t_proj FORMAT TSVRaw;
