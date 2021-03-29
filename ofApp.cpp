#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetLineWidth(2);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(295);

	for (int k = 0; k < 1; k++) {

		auto noise_seed_deg = ofRandom(1000);
		auto noise_seed_radius = ofRandom(1000);
		vector<glm::vec3> vertices;
		for (int i = 0; i < 45; i++) {

			auto noise_deg = ofMap(ofNoise(noise_seed_deg, (ofGetFrameNum() + i) * 0.006), 0, 1, -360, 360);
			auto noise_radius = ofMap(ofNoise(noise_seed_radius, (ofGetFrameNum() + i) * 0.005), 0, 1, -350, 350);
			vertices.push_back(glm::vec3(noise_radius * cos(noise_deg * DEG_TO_RAD), noise_radius * sin(noise_deg * DEG_TO_RAD), 0));
		}
		
		for (int deg = 0; deg < 360; deg += 30) {

			auto rotation = glm::rotate(glm::mat4(), deg * (float)DEG_TO_RAD, glm::vec3(0, 0, 1));

			ofMesh face, line;
			line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
			for (int i = 0; i < vertices.size(); i++) {

				face.addVertex(glm::vec4(vertices[i], 0) * rotation + glm::vec4(0, 0, -15, 0));
				face.addVertex(glm::vec4(vertices[i], 0) * rotation + glm::vec4(0, 0, 15, 0));

				line.addVertex(glm::vec4(vertices[i], 0) * rotation + glm::vec4(0, 0, -15, 0));
				line.addVertex(glm::vec4(vertices[i], 0) * rotation + glm::vec4(0, 0, 15, 0));

				if (i > 0) {

					face.addIndex(face.getNumVertices() - 1); face.addIndex(face.getNumVertices() - 2); face.addIndex(face.getNumVertices() - 4);
					face.addIndex(face.getNumVertices() - 1); face.addIndex(face.getNumVertices() - 3); face.addIndex(face.getNumVertices() - 4);

					line.addIndex(line.getNumVertices() - 1); line.addIndex(line.getNumVertices() - 3);
					line.addIndex(line.getNumVertices() - 2); line.addIndex(line.getNumVertices() - 4);

				}
			}

			line.addIndex(0); line.addIndex(1);
			line.addIndex(line.getNumVertices() - 1); line.addIndex(line.getNumVertices() - 2);

			ofSetColor(39);
			face.draw();
			ofSetColor(239);
			line.drawWireframe();
		}
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}