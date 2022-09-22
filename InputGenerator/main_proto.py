import xml.etree.ElementTree as ET
from xml.etree.ElementTree import Element, SubElement, ElementTree
import os
import random
import numpy as np

def node_ids(txt):
    if txt != '' and txt != None:
        return '1' + '0' * (7 - len(txt)) + txt
    else:
        return ''


def link_ids(txt):
    if txt != '':
        return '2' + '0' * (7 - len(txt)) + txt
    else:
        return ''


def cell_length(length, unit_time, ffspeed):
    cell_length = unit_time * ffspeed / 3.6  # in meter unit
    if length > cell_length:
        n = length // cell_length + 1  # calculate how many section is needed
        cell_length_re = length / n  # re-divide with same length
        return [cell_length_re, n]
    else:
        return [length, 1]


def wavespeed(ffspeed, jam_density, capacity):
    return 1 / ((jam_density / capacity) - (1 / ffspeed))


def turn_priority(turn):
    key = GKBezierCurve.angleToCurve(turning, turning)
    if key > -0.79 and key < 0.79:
        return '1.0'
    elif key >= 0.79:
        return '0.5'
    else:
        return '0.1'

def term(id):
	return str(int(link_ids(str(id)))-10000000+1000000)

def centroid_section_data(centroid, key):
    connectionsAtt = model.getColumn( 'GKGeoObject::connectionsAtt' )
    connectionsList = centroid.getDataValue( connectionsAtt )[0] #this is a list of centroid connection IDs
    section_info_list=[]
    for conn_id in connectionsList:
        conn = model.getCatalog().find( conn_id ) # This returns the GKCenConnection object
        if key=='origin':
            if conn.getConnectionType()==2:
                section_id = conn.getConnectionObject().getId()
                proportion=conn.getPercentage()/100
                section_info_list.append([term(section_id), proportion])
        elif key=='destination':
            if conn.getConnectionType()==1:
                section_id = conn.getConnectionObject().getId()
                proportion=conn.getPercentage()/100
                section_info_list.append([term(section_id), proportion])
    return section_info_list

def route_seq(route):
	for i,section in enumerate(route.getRoute()):

		if i==0:
			node_seq, link_seq= term(section.getId())+' '+ node_ids(str(section.getDestination().getId())), link_ids(str(section.getId()))
		elif i==len(route.getRoute())-1:
			node_seq+= ' '+term(section.getId())
			link_seq+=' '+link_ids(str(section.getId()))
		else:
			node_seq+=' '+ node_ids(str(section.getDestination().getId()))
			link_seq+=' '+link_ids(str(section.getId()))
	return [node_seq, link_seq]

def vehicle_type(txt):
	if txt=='Car':
		return 'nv'
	elif txt=='Bus':
		return 'nb'
	elif txt=='Truck':
		return 'tr'

def agent_vehicle_type(txt):
	if txt=='Car':
		return '1'
	elif txt=='Bus':
		return '3'
	elif txt=='Truck':
		return '5'

def dpt_time(trip, duration):
	flow=trip/(duration/60)
	cs=np.cumsum(np.random.exponential(1/flow, int(trip))*3600*10)
	return cs

def datasave(node_list, link_list, fileName_network, fileName_OD, fileName_agent):  # From GUI data to xml file

    root1 = Element("Network")
    root1.set('id', '0')

    sub_element = SubElement(root1, "nodes")
    for node in node_list:  # node
        sub_element1 = SubElement(sub_element, "node")
        sub_element1.set('id', node[0])
        sub_element1.set('v2x', node[1])
        sub_element1.set('type', node[2])
        sub_element1.set('num_port', node[3])
        sub_element1.set('num_connection', node[4])
        for port in node[5]:
            sub_element2 = SubElement(sub_element1, "port")
            sub_element2.set('type', port[0])
            sub_element2.set('link_id', port[1])
            sub_element2.set('direction', port[2])

        if node[2] == 'normal' or node[2] == 'intersection':
            for connection in node[6]:
                sub_element2 = SubElement(sub_element1, "connection")
                sub_element2.set('id', connection[0])
                sub_element2.set('from_link', connection[1])
                sub_element2.set('from_lane', connection[2])
                sub_element2.set('to_link', connection[3])
                sub_element2.set('to_lane', connection[4])
                sub_element2.set('ffspeed', connection[5])
                sub_element2.set('length', connection[6])
                sub_element2.set('qmax', connection[7])
                sub_element2.set('priority', connection[8])
                sub_element2.set('width', connection[9])
                sub_element2.set('waveSpd', connection[10])

        if node[2] == 'intersection':
            for phase in node[7]:
                sub_element2 = SubElement(sub_element1, "phase")
                sub_element2.set('id', phase[0])
                for phase_connection in phase[1]:
                    sub_element3 = SubElement(sub_element2, "connection")
                    sub_element3.set('priority', phase_connection[0])
                    sub_element3.set('id_ref', phase_connection[1])

        for signal_plan in node[8]:
            sub_element2 = SubElement(sub_element1, "signal_plan")
            sub_element2.set('id', signal_plan[0])
            sub_element2.set('order', signal_plan[1])
            sub_element2.set('offset', signal_plan[2])

    sub_element = SubElement(root1, "links")
    for link in link_list:  # link
        sub_element1 = SubElement(sub_element, "link")
        sub_element1.set('id', link[0])
        sub_element1.set('type', link[1])
        sub_element1.set('width', link[2])
        sub_element1.set('waveSpd', link[3])
        sub_element1.set('qmax', link[4])
        sub_element1.set('min_spd', link[5])
        sub_element1.set('max_spd', link[6])
        sub_element1.set('maxVeh', link[7])
        sub_element1.set('length', link[8])
        sub_element1.set('ffspeed', link[9])
        sub_element1.set('sim_type', link[10])
        sub_element1.set('num_lane', link[11])
        sub_element1.set('from_node', link[12])
        sub_element1.set('to_node', link[13])
        sub_element1.set('layer', link[15])
        for lane in link[14]:
            sub_element2 = SubElement(sub_element1, "lane")
            sub_element2.set('id', lane[0])
            sub_element2.set('left_lane_id', lane[1])
            sub_element2.set('right_lane_id', lane[2])
            sub_element2.set('num_cell', lane[3])
            sub_element2.set('fromX', lane[4])
            sub_element2.set('fromY', lane[5])
            sub_element2.set('toX', lane[6])
            sub_element2.set('toY', lane[7])
            for cell in lane[8]:
                sub_element3 = SubElement(sub_element2, "cell")
                sub_element3.set('id', cell[0])
                sub_element3.set('offset', cell[1])
                sub_element3.set('length', cell[2])
            for segment in lane[9]:
                sub_element3 = SubElement(sub_element2, "segment")
                sub_element3.set('id', segment[0])
                sub_element3.set('right_lc', segment[1])
                sub_element3.set('left_lc', segment[2])
                sub_element3.set('init_point', segment[3])
                sub_element3.set('end_point', segment[4])
                sub_element3.set('block', segment[5])
        for section in link[16]:
            sub_element2 = SubElement(sub_element1, "section")
            sub_element2.set('id', section[0])
            sub_element2.set('left_id', section[1])
            sub_element2.set('right_id', section[2])
            sub_element2.set('slope', section[3])
            sub_element2.set('length', section[4])
            sub_element2.set('offset', section[5])

    _pretty_print(root1)
    tree1 = ElementTree(root1)

    root3=Element('Demands')
    root4 = Element("agents")
    sub_element_a=SubElement(root4, "PublicVeh")

    for i, matrix in enumerate(od_list):
        if i!=0 and od_list[i-1][0]==od_list[i][0] and od_list[i-1][1]==od_list[i][1]:
            sub_element1 = SubElement(sub_element, vehicle_type(matrix[2])+'_od_matrix')
            for demand in matrix[3]:
                sub_element2=SubElement(sub_element1, 'demand')
                sub_element2.set('source', demand[0])
                sub_element2.set('sink', demand[1])
                sub_element2.set('flow', demand[2])
                sub_element2.set('dist', '')

            sub_element_a1 = SubElement(sub_element_a, vehicle_type(matrix[2])+'_od_matrix')
            for vehicle in matrix[4]:
                sub_element_a2 = SubElement(sub_element_a1, 'veh')
                sub_element_a2.set('id', vehicle[0])
                sub_element_a2.set('dpt_time', vehicle[1])
                sub_element_a2.set('type', vehicle[2])
                sub_element_a2.set('node_seq', vehicle[3])
                sub_element_a2.set('link_seq', vehicle[4])

        else:
            sub_element = SubElement(root3, 'od_matrix')
            sub_element.set('id', str(i))
            sub_element.set('start_time', matrix[0])
            sub_element.set('duration_min', matrix[1])
            sub_element1 = SubElement(sub_element, vehicle_type(matrix[2])+'_od_matrix')
            for demand in matrix[3]:
                sub_element2=SubElement(sub_element1, 'demand')
                sub_element2.set('source', demand[0])
                sub_element2.set('sink', demand[1])
                sub_element2.set('flow', demand[2])
                sub_element2.set('dist', '')

            sub_element_a1 = SubElement(sub_element_a, vehicle_type(matrix[2])+'_od_matrix')
            sub_element_a1.set('id', str(i))
            sub_element_a1.set('start_time', matrix[0])
            sub_element_a1.set('duration_min', matrix[1])
            for vehicle in matrix[4]:
                sub_element_a2 = SubElement(sub_element_a1, 'veh')
                sub_element_a2.set('id', vehicle[0])
                sub_element_a2.set('dpt_time', vehicle[1])
                sub_element_a2.set('type', vehicle[2])
                sub_element_a2.set('node_seq', vehicle[3])
                sub_element_a2.set('link_seq', vehicle[4])

    _pretty_print(root3)
    tree3 = ElementTree(root3)

    _pretty_print(root4)
    tree4 = ElementTree(root4)

    with open(fileName_network, "wb") as file:
        tree1.write(file, encoding='utf-8', xml_declaration=True)

    with open(fileName_OD, "wb") as file:
        tree3.write(file, encoding='utf-8', xml_declaration=True)

    with open(fileName_agent, "wb") as file:
        tree4.write(file, encoding='utf-8', xml_declaration=True)

def _pretty_print(current, parent=None, index=-1, depth=0):
    for i, node in enumerate(current):
        _pretty_print(node, current, i, depth + 1)
    if parent is not None:
        if index == 0:
            parent.text = '\n' + ('\t' * depth)
        else:
            parent[index - 1].tail = '\n' + ('\t' * depth)
        if index == len(parent) - 1:
            current.tail = '\n' + ('\t' * (depth - 1))


fileName_network = 'C:/Users/user/Desktop/Downloads/project/network_proto.xml'
fileName_OD = 'C:/Users/user/Desktop/Downloads/project/OD_proto.xml'
fileName_agent = 'C:/Users/user/Desktop/Downloads/project/agents_proto.xml'

# node data
node_list = []
node_terminal_list = []
for node in model.getCatalog().getObjectsByType(model.getType('GKNode')).values():
    id = node_ids(str(node.getId()))

    # port data
    port_list = []
    section_in, section_out = node.getEntranceSections(), node.getExitSections()
    for section in section_in:
        port_list.append(['in', link_ids(str(section.getId())), ''])
    for section in section_out:
        port_list.append(['out', link_ids(str(section.getId())), ''])
    node_type_id = GKNode.getNodeType(node)
    if node_type_id == 0:
        node_type = 'normal'
    else:
        node_type = 'intersection'

    # connection data
    connection_list = []
    connection_index_list = []
    i = 0
    for turning in node.getTurnings():
        from_origin_lane, to_origin_lane, from_destination_lane, to_destination_lane = turning.getOriginFromLane(), turning.getOriginToLane(), turning.getDestinationFromLane(), turning.getDestinationToLane()
        for j in range(to_origin_lane - from_origin_lane + 1):
            connection_list.append([str(i), link_ids(str(turning.getOrigin().getId())), str(from_origin_lane + j),
                                    link_ids(str(turning.getDestination().getId())), str(from_destination_lane + j),
                                    str(round(turning.getSpeed(), 2)), str(round(turning.length2D(), 2)),
                                    str(round(turning.getCapacity(), 2)), '', '', ''])
            connection_index_list.append(
                link_ids(str(turning.getOrigin().getId())) + str(from_origin_lane + j) + link_ids(
                    str(turning.getDestination().getId())) + str(from_destination_lane + j))
            i += 1

    # signal data
    control_plan = GKSystem.getSystem().getActiveModel().getCatalog().find(1571)
    RTOR_list = [turn for turn in node.getTurnings() if turn.getWarningIndicator() == 3]

    # phase data, signal plan data
    phase_list = []
    signal_plan_list = []
    control_junction = control_plan.getControlJunction(node)
    if control_junction != None:
        phases, offset, yellow_time = control_junction.getPhases(), control_junction.getOffset(), control_junction.getYellowTime()  # Based on yellow time is from node control plan / phase
        j = 1
        order = '1'
        duration_data = ''
        duration_set = []

        for k, phase in enumerate(phases):

            # signal plan data
            duration = phase.getDuration()

            if duration == yellow_time:  # Yellow signal : add to prior green signal
                duration_set[-1] += duration

                # phase connection data
                for phase_signal in phase.getSignals():
                    signal = node.getSignal(phase_signal.signal)
                    for turning in signal.getTurnings():
                        from_origin_lane, to_origin_lane, from_destination_lane, to_destination_lane = turning.getOriginFromLane(), turning.getOriginToLane(), turning.getDestinationFromLane(), turning.getDestinationToLane()
                        priority = turn_priority(turning)
                        for l in range(to_origin_lane - from_origin_lane + 1):
                            key = link_ids(str(turning.getOrigin().getId())) + str(
                                from_origin_lane + l) + link_ids(
                                str(turning.getDestination().getId())) + str(from_destination_lane + l)
                            id_ref = str(connection_index_list.index(key))
                            if [priority, id_ref] not in phase_connection_list:  # Avoid duplication
                                phase_connection_list.append([priority, id_ref])
                phase_list.append([str(j), phase_connection_list])

                if j != 1:
                    order += ' ' + str(j)
                    j += 1
                else:
                    j += 1

            else:  # Green signal
                duration_set.append(duration)

                # phase connection data
                phase_connection_list = []
                for a, phase_signal in enumerate(phase.getSignals()):
                    signal = node.getSignal(phase_signal.signal)
                    turnings = signal.getTurnings()
                    for turning in turnings:
                        from_origin_lane, to_origin_lane, from_destination_lane, to_destination_lane = turning.getOriginFromLane(), turning.getOriginToLane(), turning.getDestinationFromLane(), turning.getDestinationToLane()
                        priority = turn_priority(turning)
                        for l in range(to_origin_lane - from_origin_lane + 1):
                            key = link_ids(str(turning.getOrigin().getId())) + str(
                                from_origin_lane + l) + link_ids(
                                str(turning.getDestination().getId())) + str(from_destination_lane + l)
                            id_ref = str(connection_index_list.index(key))
                            phase_connection_list.append([priority, id_ref])

                for turning in RTOR_list:
                    from_origin_lane, to_origin_lane, from_destination_lane, to_destination_lane = turning.getOriginFromLane(), turning.getOriginToLane(), turning.getDestinationFromLane(), turning.getDestinationToLane()
                    priority = turn_priority(turning)
                    for l in range(to_origin_lane - from_origin_lane + 1):
                        key = link_ids(str(turning.getOrigin().getId())) + str(from_origin_lane + l) + link_ids(
                            str(turning.getDestination().getId())) + str(from_destination_lane + l)
                        id_ref = str(connection_index_list.index(key))
                        phase_connection_list.append([priority, id_ref])

                if k == len(phases) - 1:  # Green signal at the end
                    phase_list.append([str(j), phase_connection_list])

                    if j != 1:
                        order += ' ' + str(j)
                        j += 1
                    else:
                        j += 1

        for m, duration in enumerate(duration_set):
            if m != 0:
                duration_data += ' ' + str(duration)
            else:
                duration_data += str(duration)

        signal_plan_list.append([duration_data, order, str(offset)])

    node_list.append(
        [id, '', node_type, str(len(port_list)), str(len(connection_list)), port_list, connection_list, phase_list,
         signal_plan_list])

for node in node_list:
    print(node[7])

# link data
link_list = []

for section in model.getCatalog().getObjectsByType(model.getType('GKSection')).values():
    id = link_ids(str(section.getId()))
    type = 'straight'
    length = section.length2D()
    lanes = section.getLanes()
    num_lane = len(lanes)
    jam_density = section.getDataValue(model.getColumn('GKSection::jamDensityAtt'))[0] * num_lane
    qmax = section.getCapacity()
    ffspeed = section.getSpeed()
    min_speed = '0'
    max_speed = section.getSpeed()
    wave_speed = wavespeed(ffspeed, jam_density, qmax)
    max_veh = jam_density * length / 1000
    width = section.getWidth()
    sim_type = '0'
    if section.getOrigin() == None:
        from_node, to_node = str(int(link_ids(str(section.getId()))) - 10000000 + 1000000), node_ids(
            str(section.getDestination().getId()))
        node_list.append([from_node, '', 'terminal', '1', '0', [['out', id, '']], [], [], []])
        node_terminal_list.append(from_node)
    elif section.getDestination() == None:
        from_node, to_node = node_ids(str(section.getOrigin().getId())), str(
            int(link_ids(str(section.getId()))) - 10000000 + 1000000)
        node_list.append([to_node, '', 'terminal', '1', '0', [['in', id, '']], [], [], []])
        node_terminal_list.append(to_node)
    else:
        from_node, to_node = node_ids(str(section.getOrigin().getId())), node_ids(str(section.getDestination().getId()))

    # lane data
    lane_list = []
    for i, lane in enumerate(lanes):
        if i == 0:
            left_id, right_id = '', i + 1
        elif i == len(lanes) - 1:
            left_id, right_id = i - 1, ''
        else:
            left_id, right_id = i - 1, i + 1
        from_coord, to_coord = model.getGeoModel().getCoordinateTranslator().toDegrees(
            section.pointAtPos(0)), model.getGeoModel().getCoordinateTranslator().toDegrees(
            section.pointAtPos(section.length2D()))
        from_x, from_y, to_x, to_y = from_coord.x, from_coord.y, to_coord.x, to_coord.y

        # cell data
        cell_list = []
        cl = cell_length(section.getLaneLength2D(i), 5, ffspeed)
        offset = 0
        for j in range(int(cl[1])):
            cell_list.append([str(j), str(round(offset, 2)), str(round(cl[0], 2))])
            offset += cl[0]

        # segment data
        segment_list = []
        if lane.isFullLane() == False:
            io, fo = lane.getInitialOffset(), lane.getFinalOffset()
            if io != 0 and fo == 0:
                segment_list = [['0', '', '', '0', str(round(length + io, 2)), 'True'],
                                ['1', '', '', str(round(length + io, 2)), str(round(length, 2)), 'False']]
            elif io == 0 and fo != 0:
                segment_list = [['0', '', '', '0', str(round(fo, 2)), 'False'],
                                ['1', '', '', str(round(fo, 2)), str(round(length, 2)), 'True']]

        lane_list.append(
            [str(i), str(left_id), str(right_id), str(len(cell_list)), str(from_x), str(from_y), str(to_x), str(to_y),
             cell_list, segment_list])

    # section data
    section_list = []
    offset = 0
    level = section.getLayer().getLevel()
    if level == 100:
        altitude_type = ''
    else:
        for i in range(section.getNbSegments()):
            if i == 0:
                section_list.append([str(i), '', str(i + 1), str(round(section.getSlope(i), 2)),
                                     str(round(section.getSegmentLength(i), 2)), str(round(offset, 2))])
                offset += round(section.getSegmentLength(i), 2)
            elif i == section.getNbSegments() - 1:
                section_list.append([str(i), str(i - 1), '', str(round(section.getSlope(i), 2)),
                                     str(round(section.getSegmentLength(i), 2)), str(round(offset, 2))])
                offset += round(section.getSegmentLength(i), 2)
            else:
                section_list.append([str(i), str(i - 1), str(i + 1), str(round(section.getSlope(i), 2)),
                                     str(round(section.getSegmentLength(i), 2)), str(round(offset, 2))])
                offset += round(section.getSegmentLength(i), 2)

        if level < 0:
            altitude_type = 'underpass'
        elif level > 0:
            altitude_type = 'overpass'

    link_list.append(
        [id, type, str(round(width, 2)), str(round(wave_speed, 2)), str(round(qmax)), min_speed, str(round(max_speed)),
         str(round(max_veh)), str(round(length)), str(round(ffspeed)), str(sim_type), str(num_lane), str(from_node),
         str(to_node), lane_list, altitude_type, section_list])

#OD, agents data
od_list=[]

for matrix in model.getCatalog().getObjectsByType(model.getType('GKODMatrix')).values():
	#OD data
	start_time, duration, vehicle_class=matrix.getFrom().toString('hh:mm:ss'), matrix.getDuration().toMinutes(), matrix.getVehicle().getName()
	centroids = matrix.getCentroidConfiguration().getCentroidsInOrder()
	od_section_list=[]

	for origin in centroids:
		for destination in centroids:
			if origin != destination:
				trips = matrix.getTrips( origin, destination )
				if trips !=0:
					origin_section_data, destination_section_data=centroid_section_data(origin, 'origin'), centroid_section_data(destination, 'destination')
					od_section_list.extend([[o_data[0],d_data[0], str(round(trips*o_data[1]*d_data[1]/duration*60,2))] for o_data in origin_section_data for d_data in destination_section_data])

	#agents data
	agent_list=[]
	for route in matrix.getRoutes():
		route_origin_centroid, route_destination_centroid=route.getOriginCentroid(), route.getDestinationCentroid()
		trips = matrix.getTrips(route_origin_centroid, route_destination_centroid)
		seq=route_seq(route)
		node_seq, link_seq=seq[0], seq[1]
		route_trip=trips*matrix.getRoutePercentage(route)/100
		num_agent=dpt_time(route_trip, duration)
		for i, dt in enumerate(num_agent):
			agent_list.append([str(i), str(round(dt)) , agent_vehicle_type(vehicle_class), node_seq, link_seq])

	od_list.append([str(start_time), str(duration), vehicle_class, od_section_list, agent_list])

od_list=sorted(od_list, key=lambda x: (int(str(x[0][0:2])+str(x[0][3:5])+str(x[0][6:8])), float(x[1])) )

datasave(node_list, link_list, fileName_network, fileName_OD, fileName_agent)