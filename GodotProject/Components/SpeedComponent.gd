@tool
extends Component
class_name SpeedComponent

<<<<<<< HEAD

func get_component() -> Dictionary[String, Variant]:
	return {
=======
@export var speed:float

func get_component() -> Dictionary[String, Variant]:
	return {
		"speed" : FormatWriter.format(speed, "speed"),
>>>>>>> f2e822d (proyecto de godot en proceso)
	}
