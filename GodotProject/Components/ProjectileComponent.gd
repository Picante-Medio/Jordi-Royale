@tool
extends Component
class_name ProjectileComponent

@export var lifetime:int
@export var speed:float

func get_component() -> Dictionary[String, Variant]:
	return {
		"lifetime" : FormatWriter.format(lifetime, "lifetime"),
		"speed" : FormatWriter.format(speed, "speed"),
	}
