@tool
extends Component
class_name PlayerComponent

@export var jumpPower:float = 500.0
@export var pickupRange:float = 5.0
@export var airJumps:int = 0

func get_component() -> Dictionary[String, Variant]:
	return {
		"jumpPower" : FormatWriter.format(jumpPower, "jumpPower"),
		"pickupRange" : FormatWriter.format(pickupRange, "pickupRange"),
		"airJumps" : FormatWriter.format(airJumps, "airJumps"),
	}
