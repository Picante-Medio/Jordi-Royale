@icon("res://addons/HugosChatPlugin/Icons/scene_tracker_icon.png")
@tool
extends Node3D
class_name SCENE_TRACKER

@export var systems:Array[SYSTEMS.system] = [
	SYSTEMS.system.AudioSystem,
	SYSTEMS.system.PhysicsGizmoSystem,
	SYSTEMS.system.HierarchySystem,
	SYSTEMS.system.ParticleSystem,
	SYSTEMS.system.CameraSystem,
	SYSTEMS.system.LightSystem,
	SYSTEMS.system.RenderSystem,
	SYSTEMS.system.TweenSystem,
	SYSTEMS.system.UISystem,
	SYSTEMS.system.ConsoleSystem
]

@export_tool_button("Save Scene") var button = SceneWriter.write
var entities:Array[EntityData]

func track_entities():
	entities.clear()
	if self is Entity: entities.push_back(add_entity(self))
	else:
		for node_child in self.get_children():
			if node_child is Entity:
				entities.push_back(add_entity(node_child))

#Returns entityData with components and children, which are more entityData
func add_entity(entity:Entity) -> EntityData:
	print(entity.name)
	var entity_data:EntityData = EntityData.new()
	entity_data.entityName = entity.name
	if entity is Entity3D:
			entity_data.components.get_or_add("TransformComponent", entity.get_component())
			
	for node_child in entity.get_children():
		if node_child is Entity:
			entity_data.children.push_back(add_entity(node_child))
		elif node_child.has_method("get_component"):
			var child_class_name:String = node_child.get_script().resource_path.get_file().split(".gd")[0]
			entity_data.components.get_or_add(child_class_name, node_child.get_component())
			
	return entity_data
