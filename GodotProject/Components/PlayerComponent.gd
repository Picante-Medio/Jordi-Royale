@tool
extends Component
class_name PlayerComponent

@export var jumpPower:float = 500.0
@export var xpPickupRange:float = 5.0
@export var objectPickupRange:float = 1.0
@export var airJumps:int = 0

func get_component() -> Dictionary[String, Variant]:
	return {
		"jumpPower" : FormatWriter.format(jumpPower, "jumpPower"),
		"xpPickupRange" : FormatWriter.format(xpPickupRange, "xpPickupRange"),
		"objectPickupRange" : FormatWriter.format(objectPickupRange, "objectPickupRange"),
		"airJumps" : FormatWriter.format(airJumps, "airJumps"),
	}
