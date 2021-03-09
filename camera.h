class Camera {
 public:
    Camera();
    
    // many familiar helper functions such as
    void LookAt(glm::vec3 eye, glm::vec3 cen, glm::vec3 up);
    // and of course
    void Render(Scene &s);
    void SaveImage(char *filename);
 private:
    int width, height;
    glm::vec3 pos, u, v, w;
    float fovy;
    float aspect;
    Image image;
};