# generated from rosidl_generator_py/resource/_idl.py.em
# with input from sonar_msgs:msg/ThreeSonarDepth.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_ThreeSonarDepth(type):
    """Metaclass of message 'ThreeSonarDepth'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('sonar_msgs')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'sonar_msgs.msg.ThreeSonarDepth')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__three_sonar_depth
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__three_sonar_depth
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__three_sonar_depth
            cls._TYPE_SUPPORT = module.type_support_msg__msg__three_sonar_depth
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__three_sonar_depth

            from std_msgs.msg import Header
            if Header.__class__._TYPE_SUPPORT is None:
                Header.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class ThreeSonarDepth(metaclass=Metaclass_ThreeSonarDepth):
    """Message class 'ThreeSonarDepth'."""

    __slots__ = [
        '_header',
        '_distance_1',
        '_confidence_1',
        '_distance_2',
        '_confidence_2',
        '_distance_3',
        '_confidence_3',
        '_depth',
        '_altitude',
        '_pressure',
    ]

    _fields_and_field_types = {
        'header': 'std_msgs/Header',
        'distance_1': 'float',
        'confidence_1': 'float',
        'distance_2': 'float',
        'confidence_2': 'float',
        'distance_3': 'float',
        'confidence_3': 'float',
        'depth': 'float',
        'altitude': 'float',
        'pressure': 'float',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Header'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from std_msgs.msg import Header
        self.header = kwargs.get('header', Header())
        self.distance_1 = kwargs.get('distance_1', float())
        self.confidence_1 = kwargs.get('confidence_1', float())
        self.distance_2 = kwargs.get('distance_2', float())
        self.confidence_2 = kwargs.get('confidence_2', float())
        self.distance_3 = kwargs.get('distance_3', float())
        self.confidence_3 = kwargs.get('confidence_3', float())
        self.depth = kwargs.get('depth', float())
        self.altitude = kwargs.get('altitude', float())
        self.pressure = kwargs.get('pressure', float())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.header != other.header:
            return False
        if self.distance_1 != other.distance_1:
            return False
        if self.confidence_1 != other.confidence_1:
            return False
        if self.distance_2 != other.distance_2:
            return False
        if self.confidence_2 != other.confidence_2:
            return False
        if self.distance_3 != other.distance_3:
            return False
        if self.confidence_3 != other.confidence_3:
            return False
        if self.depth != other.depth:
            return False
        if self.altitude != other.altitude:
            return False
        if self.pressure != other.pressure:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def header(self):
        """Message field 'header'."""
        return self._header

    @header.setter
    def header(self, value):
        if __debug__:
            from std_msgs.msg import Header
            assert \
                isinstance(value, Header), \
                "The 'header' field must be a sub message of type 'Header'"
        self._header = value

    @builtins.property
    def distance_1(self):
        """Message field 'distance_1'."""
        return self._distance_1

    @distance_1.setter
    def distance_1(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'distance_1' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'distance_1' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._distance_1 = value

    @builtins.property
    def confidence_1(self):
        """Message field 'confidence_1'."""
        return self._confidence_1

    @confidence_1.setter
    def confidence_1(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'confidence_1' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'confidence_1' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._confidence_1 = value

    @builtins.property
    def distance_2(self):
        """Message field 'distance_2'."""
        return self._distance_2

    @distance_2.setter
    def distance_2(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'distance_2' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'distance_2' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._distance_2 = value

    @builtins.property
    def confidence_2(self):
        """Message field 'confidence_2'."""
        return self._confidence_2

    @confidence_2.setter
    def confidence_2(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'confidence_2' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'confidence_2' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._confidence_2 = value

    @builtins.property
    def distance_3(self):
        """Message field 'distance_3'."""
        return self._distance_3

    @distance_3.setter
    def distance_3(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'distance_3' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'distance_3' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._distance_3 = value

    @builtins.property
    def confidence_3(self):
        """Message field 'confidence_3'."""
        return self._confidence_3

    @confidence_3.setter
    def confidence_3(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'confidence_3' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'confidence_3' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._confidence_3 = value

    @builtins.property
    def depth(self):
        """Message field 'depth'."""
        return self._depth

    @depth.setter
    def depth(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'depth' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'depth' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._depth = value

    @builtins.property
    def altitude(self):
        """Message field 'altitude'."""
        return self._altitude

    @altitude.setter
    def altitude(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'altitude' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'altitude' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._altitude = value

    @builtins.property
    def pressure(self):
        """Message field 'pressure'."""
        return self._pressure

    @pressure.setter
    def pressure(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'pressure' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'pressure' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._pressure = value
