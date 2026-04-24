@tool
extends Component
class_name HPComponent

<<<<<<< HEAD

func get_component() -> Dictionary[String, Variant]:
	return {
=======
@export var HPMax:int
@export var CurrentHP:int

func get_component() -> Dictionary[String, Variant]:
	return {
		"HPMax" : FormatWriter.format(HPMax, "HPMax"),
		"CurrentHP" : FormatWriter.format(CurrentHP, "CurrentHP"),
>>>>>>> f2e822d (proyecto de godot en proceso)
	}
