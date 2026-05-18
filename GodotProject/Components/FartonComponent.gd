@tool
extends Component
class_name FartonComponent

@export var maxDist:float = 15.0
@export var speed:float = 6.0

func get_component() -> Dictionary[String, Variant]:
	return {
		"maxDist" : FormatWriter.format(maxDist, "maxDist"),
		"speed" : FormatWriter.format(speed, "speed"),
	}
