@tool
extends Component
class_name LevelComponent

@export var level:int = 1

func get_component() -> Dictionary[String, Variant]:
	return {
		"level" : FormatWriter.format(level, "level"),
	}
