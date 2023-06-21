import classNames from 'classnames';
import { useState } from 'react';
import { useRouter } from 'next/router';
import styles from '../styles/Signin.module.css';
import { axiosInstance } from '@/utils/axiosInstance';

export default function Signin() {
  const router = useRouter();
  const [email, setEmail] = useState('');
  const [password, setPassword] = useState('');
  const [errors, setErrors] = useState({});

  const checkSignIn = () => {
    const validationErrors = {};
    let isValid = true;

    if (!email) {
      validationErrors.email = 'Email is required';
      isValid = false;
    } else if (!/\S+@\S+\.\S+/.test(email)) {
      validationErrors.email = 'Email is not valid';
      isValid = false;
    }

    if (!password) {
      validationErrors.password = 'Password is required';
      isValid = false;
    } else if (password.length < 6) {
      validationErrors.password = 'Password must be at least 6 characters';
      isValid = false;
    }

    setErrors(validationErrors);
    return isValid;
  };

  const handleSubmit = async (event) => {
    event.preventDefault();

    if (!checkSignIn()) {
      return;
    }

    try {
      // Disable submit button while the form is being submitted
      event.target.elements.submitButton.disabled = true;

      await axiosInstance.post('/api/signIn', { email, password });
      router.push('/');
    } catch (error) {
      console.error(error);
      alert('Login failed. Please check your credentials.');
    } finally {
      // Re-enable the submit button
      event.target.elements.submitButton.disabled = false;
    }
  };

  return (
    <div className={styles.signinNew}>
      <nav>
        <ul>
          <li>
            <a href="/">Home</a>
          </li>
          <li>
            <a href="signup">Sign Up</a>
          </li>
          <li>
            <a href="/contact">Contact</a>
          </li>
        </ul>
      </nav>
      <main className={classNames(styles.formSignin, 'text-center', 'mt-5')}>
        <h1 className="h3 mb-3 fw-normal">RIOT Sign in</h1>
        <div className="form-floating">
          <form onSubmit={handleSubmit}>
            <div className={styles.formGroup}>
              <label htmlFor="email" className={styles.label}>
                Email
                <input
                  type="email"
                  id="email"
                  className="form-control"
                  placeholder="Enter Email"
                  value={email}
                  onChange={(e) => setEmail(e.target.value)}
                  aria-label="Email"
                />
                {errors.email && <span className={styles.error}>{errors.email}</span>}
              </label>
            </div>

            <div className={styles.formGroup}>
              <label htmlFor="password" className={styles.label}>
                Password
                <input
                  type="password"
                  id="password"
                  className="form-control"
                  placeholder="Password"
                  value={password}
                  onChange={(e) => setPassword(e.target.value)}
                  aria-label="Password"
                />
                {errors.password && <span className={styles.error}>{errors.password}</span>}
              </label>
            </div>

            <div className={classNames(styles.checkbox, 'mb')}>
              <label>
                <input type="checkbox" value="remember-me" /> Remember me
              </label>
            </div>
            <button type="submit" name="submitButton">Sign in</button>
            <footer>
              <p>
                If you don't have an account, please <a href="/signup">sign up here</a>.
              </p>
            </footer>
          </form>
        </div>
      </main>
    </div>
  );
}
