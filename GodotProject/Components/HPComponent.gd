@tool
extends Component
class_name HPComponent

@export var HPMax:int = 100
@export var CurrentHP:int = 100

func get_component() -> Dictionary[String, Variant]:
	return {
		"HPMax" : FormatWriter.format(HPMax, "HPMax"),
		"CurrentHP" : FormatWriter.format(CurrentHP, "CurrentHP"),
	}
