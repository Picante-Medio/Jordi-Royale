@tool
extends Component
class_name RotateComponent

@export var speed:float = 5.

func get_component() -> Dictionary[String, Variant]:
	return {
		"speed" : FormatWriter.format(speed, "speed"),
	}
